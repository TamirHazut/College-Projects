#include <cuda_runtime.h>
#include <helper_cuda.h>
#include <stdlib.h>
#include "myProto.h"


__global__  void calcBucketsKernel(int *arr, int part, int *bucket, int numOfBlocks, int numOfThreadsPerBlock) {
	int tid, blockId, start, end, bucketStart, i;

	tid = threadIdx.x;
	blockId = blockIdx.x;

	start = tid*part;
	end = start+part;

	if (tid < numOfThreadsPerBlock)
	{
		bucketStart = (blockId * numOfThreadsPerBlock + tid) * BUCKET_SIZE;
		for (i = start; i < end; ++i)
		{
			bucket[bucketStart + arr[i]]++;
		}
	}
}

__global__  void sumBucketsKernel(int *histogram, int *bucket, int numOfBlocks, int numOfThreadsPerBlock) {
	int tid, i, j;

	tid = threadIdx.x;

	for (i = 0; i < numOfBlocks; ++i)
	{
		for (j = 0; j < numOfThreadsPerBlock; ++j)
		{
			histogram[tid] += bucket[(i*numOfThreadsPerBlock + j)*BUCKET_SIZE+tid];\
		}
	}
}


int* histogramUsingCuda(int *arr, int arrSize) {

    // Error code to check return values for CUDA calls
    cudaError_t err = cudaSuccess;

    int threadsPerBlock, blocksPerGrid, *histogram;
    size_t size = arrSize * sizeof(int);

    threadsPerBlock = 32;
    blocksPerGrid = 2;

    // Allocate memory on GPU to copy the data from the host
    int *d_A;
    err = cudaMalloc((void **)&d_A, size);
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to allocate device memory - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Copy data from host to the GPU memory
    err = cudaMemcpy(d_A, arr, size, cudaMemcpyHostToDevice);
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to copy data from host to device - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

   // Allocate memory on GPU for each bucket
    int *bucket;
    err = cudaMalloc((void **)&bucket, threadsPerBlock * blocksPerGrid * BUCKET_SIZE * sizeof(int));
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to allocate device memory - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Reset bucket to 0 value
    err = cudaMemset(bucket, 0, threadsPerBlock * blocksPerGrid * BUCKET_SIZE * sizeof(int));
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to reset allocated memory - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

   // Allocate memory on GPU for each bucket
    int *temp_histogram;
    err = cudaMalloc((void **)&temp_histogram, BUCKET_SIZE * sizeof(int));
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to allocate device memory - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Reset bucket to 0 value
    err = cudaMemset(temp_histogram, 0, BUCKET_SIZE * sizeof(int));
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to reset allocated memory - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Launch the calculation Kernel
    calcBucketsKernel<<<blocksPerGrid, threadsPerBlock>>>(d_A, arrSize/(threadsPerBlock*blocksPerGrid), bucket, blocksPerGrid, threadsPerBlock);
    err = cudaGetLastError();
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to launch calcBucketsKernel -  %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaDeviceSynchronize();
    if (err != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error after launching calcBucketsKernel -  %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Launch the sum Kernel
    sumBucketsKernel<<<1, BUCKET_SIZE>>>(temp_histogram, bucket, blocksPerGrid, threadsPerBlock);
    err = cudaGetLastError();
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to launch sumBucketsKernel -  %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaDeviceSynchronize();
    if (err != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error after launching sumBucketsKernel -  %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Copy the  result from GPU to the host memory.
    histogram = (int*) malloc(sizeof(int) * BUCKET_SIZE);
    if (!histogram)
    {
	fprintf(stderr, "Could not allocate array\n");
	exit(EXIT_FAILURE);	
    }
    err = cudaMemcpy(histogram, temp_histogram, sizeof(int) * BUCKET_SIZE, cudaMemcpyDeviceToHost);
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to copy result array from device to host -%s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Free allocated memory on GPU
    if (cudaFree(d_A) != cudaSuccess) {
        fprintf(stderr, "Failed to free device data - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Free allocated memory on GPU
    if (cudaFree(bucket) != cudaSuccess) {
        fprintf(stderr, "Failed to free device data - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    // Free allocated memory on GPU
    if (cudaFree(temp_histogram) != cudaSuccess) {
        fprintf(stderr, "Failed to free device data - %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    return histogram;
}

