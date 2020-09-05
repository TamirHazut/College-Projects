#include <mpi.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include "myProto.h"


int main(int argc, char *argv[])
{
   int size, rank, i;
   int *arr;
   int *histogramArr;
   MPI_Status status;

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   if (size != 2)
   {
      printf("Run the example with two processes only\n");
      MPI_Abort(MPI_COMM_WORLD, __LINE__);
   }
   if (argc != 2)
   {
      printf("Missing args, Run command 'make run FILE=<filename>'\n");
      MPI_Abort(MPI_COMM_WORLD, __LINE__);
   }
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   // Divide the tasks between both processes
   if (rank == 0)
   {
      int arrSize;
      FILE *file;

      file = openFile(argv[1]);
      arrSize = readSizeFromFile(file);
      arr = readArrFromFile(file, arrSize);

      size = (arrSize/2);
      MPI_Send(&size, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

      MPI_Send(arr + size, size, MPI_INT, 1, 0, MPI_COMM_WORLD);
   }
   else
   {
      // Allocate memory and reieve a half of array from other process
      MPI_Recv(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      arr = (int *)malloc(size * sizeof(int));
      if (!arr)
      {
	 fprintf(stderr, "Could not allocate array\n");
         MPI_Abort(MPI_COMM_WORLD, __LINE__);
      }
      MPI_Recv(arr, size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
   }
   histogramArr = calcHistogram(arr, size);

   // Collect the result on one of processes
   if (rank == 0)
   {
	int* temp_res, i;
	temp_res = (int *)malloc(BUCKET_SIZE * sizeof(int));
	if (!temp_res)
      	{
		 fprintf(stderr, "Could not allocate array\n");
        	 MPI_Abort(MPI_COMM_WORLD, __LINE__);
    	}
      	MPI_Recv(temp_res, BUCKET_SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
#pragma omp parallel for
	for (i = 0; i < BUCKET_SIZE; ++i) {
		histogramArr[i] += temp_res[i];
	}
	for (i = 0; i < BUCKET_SIZE; ++i) {
		printf("%d ", histogramArr[i]);
	}
	printf("\n");
	free(temp_res);
   }
   else
   {
      MPI_Send(histogramArr, BUCKET_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
   }
   free(histogramArr);
   free(arr);

   MPI_Finalize();

   return 0;
}
