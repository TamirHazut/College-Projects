#include <omp.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "OpenMPFunc.h"
#include "GeneralFunc.h"
#include "CudaFunc.h"

int calculateScore(double *results, int length)
{
	int i, numOfThreads, tid, bestMutant;
	int *bestMutants;
	double score;
#pragma omp parallel private(tid, score)
	{
		tid = omp_get_thread_num();
#pragma omp single
		{
			numOfThreads = omp_get_num_threads();
			bestMutant = 0;
			bestMutants = (int *)malloc(
				sizeof(int) * numOfThreads); // Allocating space for each thread to hold his best mutant index that he encountered
			if (!bestMutants)
			{
				fprintf(stderr, "Could not allocate tempResult\n");
				MPI_Abort(MPI_COMM_WORLD, __LINE__);
			}
		}
		score = -INFINITY;
#pragma omp for
		for (i = 0; i < length; i++)
		{
			if (results[i] > score) // Each thread keeps track on the best mutant index with the highest score that it was encountered
			{
				bestMutants[tid] = i;
				score = results[i];
			}
		}
	}
	for (i = 0; i < numOfThreads; i++)
	{
		if (results[bestMutants[i]] > results[bestMutant]) // Searching for the best mutant index from all the mutant indexes that was saved by the threads
		{
			bestMutant = bestMutants[i];
		}
	}
	free(bestMutants);
	return bestMutant;
}
