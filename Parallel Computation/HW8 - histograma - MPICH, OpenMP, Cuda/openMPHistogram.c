#include <omp.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "myProto.h"

int* histogramUsingOpenMP(int* arr, int size) {
	int numThreads, tid;
	int *bucket, *result;

	/* This creates a team of threads; each thread has own copy of variables  */
#pragma omp parallel private(tid) shared(numThreads, arr, size, bucket, result)
	{
		tid = omp_get_thread_num();
		numThreads = omp_get_num_threads();
#pragma omp single
	{
		bucket = (int*) malloc(sizeof(int) * numThreads * BUCKET_SIZE);
		if (!bucket)
		{
			fprintf(stderr, "Could not allocate array\n");
     	 		MPI_Abort(MPI_COMM_WORLD, 1);	
		}
		result = (int*) malloc(sizeof(int) * BUCKET_SIZE);
		if (!result)
		{
			fprintf(stderr, "Could not allocate array\n");
     	 		MPI_Abort(MPI_COMM_WORLD, 1);	
		}
	}
#pragma omp for
		for (int i = 0; i < BUCKET_SIZE * numThreads; ++i) {
			if (i < BUCKET_SIZE) {
				result[i] = 0;
			}
			bucket[i] = 0;
		}
#pragma omp for
		for (int i = 0; i < size; ++i) {
			bucket[tid * BUCKET_SIZE + arr[i]]++;
		}
#pragma omp for
		for (int i = 0; i < BUCKET_SIZE; ++i) {
			for (int j = 0; j < numThreads; ++j) {
				result[i] += bucket[i + (j * BUCKET_SIZE)];
			}
		}
	}
	free(bucket);
	return result;
}


