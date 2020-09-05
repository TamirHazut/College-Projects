#include <cuda_runtime.h>
#include <helper_cuda.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "CudaFunc.h"
#include "OpenMPFunc.h"
#include "GeneralFunc.h"

__constant__ float cudaCompareTable[26][26];

__global__ void compareTwoSequences(char *cuda_seq1, char *cuda_seq2, double *cuda_results, int length, int offset, ScoreWeight weight)
{
	int tid, blockSize, blockId, index, i;
	double score;

	tid = threadIdx.x;
	blockSize = blockDim.x;
	blockId = blockIdx.x;
	index = ((blockId * blockSize) + tid);

	if (index < length)
	{
		score = 0;
		for (i = 0; i < length; i++)
		{
			if (!index || i < index)
			{
				score += cudaCompareTable[(int)(cuda_seq1[i + offset] - 'A')][(int)(cuda_seq2[i] - 'A')];
			}
			else if (i == index)
			{
				score -= weight.w4;
				i++;
			}
			else
			{
				score += cudaCompareTable[(int)(cuda_seq1[i + offset] - 'A')][(int)(cuda_seq2[i - 1] - 'A')];
			}
		}
		cuda_results[index] = score; // Each thread calculate a single offset and mutant combination score
	}
}

void *allocateDeviceMemory(int size)
{
	cudaError_t err = cudaSuccess;
	void *memory;
	err = cudaMalloc((void **)&memory, size);
	if (err != cudaSuccess)
	{
		fprintf(stderr, "Failed to allocate device memory for cuda_seq1 - %s\n",
				cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	return memory;
}

void copyToMemory(void *to, void *from, int size, int dir)
{
	// dir = 1 -> Copy from host to the device
	// dir = 0 -> Copy from device to the host
	cudaError_t err = cudaSuccess;
	err = cudaMemcpy(to, from, size, (dir ? cudaMemcpyHostToDevice : cudaMemcpyDeviceToHost));
	if (err != cudaSuccess)
	{
		fprintf(stderr, "Failed to copy from %s - %s\n", (dir ? "host to device" : "device to host"),
				cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}
}

void freeDeviceMemory(void *memory)
{
	cudaError_t err = cudaSuccess;
	if (cudaFree(memory) != cudaSuccess)
	{
		fprintf(stderr, "Failed to free allocated memory from device - %s\n",
				cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}
}

BestMatch findBestMatchingComparison(Sequence sequence1, Sequence sequence2, float *compareTable, int lowOffset, int highOffset, ScoreWeight weight)
{
	cudaError_t err = cudaSuccess;
	cudaDeviceProp property;
	char *cuda_seq1, *cuda_seq2;
	double *cuda_results, *results;
	int threadsPerBlock, blocksPerGrid, i, j, resultLength, bestMutant;
	BestMatch bestMatch;

	// Initial settings
	bestMatch.offset = 0;
	bestMatch.mutantIndex = 0;
	bestMatch.score = -INFINITY;
	resultLength = sequence2.length + 1;

	/* 
	* Trying to use 1 block for each comparison for more use of cuda threads
	* Max threads per block: 1024
	* Max length of sequence2: 2000
	* Max blocks per sequence2: 2
	*/
	cudaGetDeviceProperties(&property, 0);
	threadsPerBlock = (property.maxThreadsPerBlock > resultLength ? resultLength : property.maxThreadsPerBlock);
	blocksPerGrid = (resultLength / threadsPerBlock) + (resultLength % threadsPerBlock != 0);

	// Allocate memory on GPU device
	cuda_seq1 = (char*)allocateDeviceMemory(sequence1.length);
	cuda_seq2 = (char*)allocateDeviceMemory(sequence2.length);
	cuda_results = (double*)allocateDeviceMemory(resultLength*sizeof(double));

	// Copy the sequences from host to the GPU memory
	copyToMemory(cuda_seq1, sequence1.seq, sequence1.length, 1);
	copyToMemory(cuda_seq2, sequence2.seq, sequence2.length, 1);

	// Copy the compare table to cuda
	err = cudaMemcpyToSymbol(cudaCompareTable, compareTable, sizeof(float) * COMPARE_TABLE_SIZE * COMPARE_TABLE_SIZE);
	if (err != cudaSuccess)
	{
		fprintf(stderr, "Failed to copy compareTable from host to GPU memory - %s\n",
				cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	// Allocate memory on host to copy the comparison result from the GPU
	results = (double *)malloc(sizeof(double) * resultLength);
	if (!results)
	{
		fprintf(stderr, "Failed to allocate results\n");
		exit(EXIT_FAILURE);
	}

	for (i = lowOffset; i < highOffset; i++)
	{
		// Compare two sequences
		compareTwoSequences<<<blocksPerGrid, threadsPerBlock>>>(cuda_seq1, cuda_seq2, cuda_results, resultLength - (!i ? 1 : 0), i, weight);

		// Copy result from the GPU to host memory
		err = cudaMemcpy(results, cuda_results, resultLength*sizeof(double), cudaMemcpyDeviceToHost);
		if (err != cudaSuccess)
		{
			fprintf(stderr,
					"Failed to copy cuda_result from GPU to host memory - %s\n",
					cudaGetErrorString(err));
			exit(EXIT_FAILURE);
		}

		// Sending to OpenMP to calculate the score
		bestMutant = calculateScore(results, sequence2.length + (j > 0 ? 1 : 0));

		// Keeping the highest score details in a variable (bestMatch)
		if (results[bestMutant] > bestMatch.score)
		{
			bestMatch.offset = i;
			bestMatch.mutantIndex = bestMutant;
			bestMatch.score = results[bestMutant];
		}
	}

	// Free allocated memory on GPU device
	freeDeviceMemory(cuda_seq1);
	freeDeviceMemory(cuda_seq2);
	freeDeviceMemory(cuda_results);

	free(results);
	return bestMatch;
}
