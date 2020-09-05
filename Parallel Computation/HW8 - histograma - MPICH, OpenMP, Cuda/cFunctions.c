#include <omp.h>
#include <mpi.h>
#include "myProto.h"
#include <stdio.h>
#include <stdlib.h>

int readSizeFromFile(FILE *file)
{
   int size;
   if (fscanf(file, "%d", &size) != 1)
   {
      fprintf(stderr, "line %d: Cannot read from file.", __LINE__);
      MPI_Abort(MPI_COMM_WORLD, 1);
   }
   return size;
}

int* readArrFromFile(FILE *file, int size)
{
   int* arr, i;
   arr = (int*) malloc(size*sizeof(int));
   if (!arr) {
      fprintf(stderr, "Could not allocate array\n");
      MPI_Abort(MPI_COMM_WORLD, 1);
   }
   for (i = 0; i < size; ++i)
   {
      if (fscanf(file, "%d", &arr[i]) != 1)
      {
         fprintf(stderr, "line %d: Cannot read from file.", __LINE__);
         MPI_Abort(MPI_COMM_WORLD, 1);
      }
   }
   fclose(file);
   return arr;
}

FILE* openFile(char *filename)
{
   FILE *file = fopen(filename, "r");
   if (!file)
   {
      fprintf(stderr, "Could not open file: %s\n", filename);
      MPI_Abort(MPI_COMM_WORLD, 1);
   }
   return file;
}

int* calcHistogram(int* arr, int size)
{
	int *histogram, *histogramArrFromOpenMP, *histogramArrFromCuda;
	histogramArrFromOpenMP = histogramUsingOpenMP(arr, size/2);
	histogramArrFromCuda = histogramUsingCuda(arr+size/2, size/2);
	histogram = (int*) malloc(sizeof(int) * BUCKET_SIZE);
	if (!histogram)
	{
		fprintf(stderr, "Could not allocate array\n");
 		MPI_Abort(MPI_COMM_WORLD, 1);	
	}
#pragma omp for
	for (int i = 0; i < BUCKET_SIZE; ++i) {
		histogram[i] = 0;
		histogram[i] += histogramArrFromOpenMP[i] + histogramArrFromCuda[i];
	}
	free(histogramArrFromOpenMP);
	free(histogramArrFromCuda);
	return histogram;
}
