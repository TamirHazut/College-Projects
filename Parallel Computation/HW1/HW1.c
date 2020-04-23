#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"

#define HEAVY 100000
#define SHORT 1
#define LONG 10

// This function performs heavy computations,
// its run time depends on x and y values
double heavy(int x, int y) {
	int i, loop = SHORT;
	double sum = 0;

// Super heavy tasks
	if (x < 3 || y < 3)
		loop = LONG;
	// Heavy calculations
	for (i = 0; i < loop * HEAVY; i++)
		sum += cos(exp(sin((double) i / HEAVY)));

	return sum;
}

double sequential_approach(int N) {
	int x, y;
	double answer = 0;
	for (x = 0; x < N; x++)
		for (y = 0; y < N; y++)
			answer += heavy(x, y);
	return answer;
}

// The master splits the work by splitting the indexes by the total amount of slaves
double static_master(int N, int numprocs, int *runIndexes, int tag,
		MPI_Status status) {
	double num_of_slaves = (numprocs - 1), answer = 0,
			amount_of_work_for_slave = ceil(N / num_of_slaves);
	for (int i = 1; i < numprocs - 1; i++) {
		runIndexes[0] = (i - 1) * amount_of_work_for_slave;
		runIndexes[1] = runIndexes[0] + amount_of_work_for_slave;
		MPI_Send(runIndexes, 2, MPI_INT, i, tag, MPI_COMM_WORLD);
	}
	runIndexes[0] = runIndexes[1];
	runIndexes[1] = N;
	MPI_Send(runIndexes, 2, MPI_INT, numprocs - 1, tag, MPI_COMM_WORLD);
	double temp_answer = 0;
	for (int i = 1; i < numprocs; i++) {
		MPI_Recv(&temp_answer, 1, MPI_DOUBLE, MPI_ANY_SOURCE, tag,
		MPI_COMM_WORLD, &status);
		answer += temp_answer;
	}
	return answer;
}

void static_slave(int N, int *runIndexes, int tag, MPI_Status status) {
	int dest = 0;
	double answer = 0;
	MPI_Recv(runIndexes, 2, MPI_INT, dest, tag, MPI_COMM_WORLD, &status);
	for (int x = runIndexes[0]; x < runIndexes[1]; x++)
		for (int y = 0; y < N; y++)
			answer += heavy(x, y);
	MPI_Send(&answer, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
}

double parallel_heavy_using_static_approach(int myid, int N, int numprocs,
		int tag, MPI_Status status) {
	int runIndexes[2] = { -1, -1 }; // index 0 for start, index 1 for end
	if (myid == 0) {
		return static_master(N, numprocs, runIndexes, tag, status);
	} else {
		static_slave(N, runIndexes, tag, status);
		return -1;
	}
}

// The master starts by giving each slave a task if he has one, otherwise he kills the slaves.
// After that the master waits for a response and than gives him a new task untill he doesn't have anymore
double dynamic_master(int N, int numprocs, int *heavyParams, int tag,
		MPI_Status status) {
	int terminated = 0;
	int terminateParams[2] = { -1, -1 };
	double answer = 0, temp_answer = 0;
	for (int i = 1; i < numprocs; i++) {
		heavyParams[1]++;
		MPI_Send(heavyParams, 2, MPI_INT, i, tag, MPI_COMM_WORLD);
	}
	do {
		MPI_Recv(&temp_answer, 1, MPI_DOUBLE, MPI_ANY_SOURCE, tag,
		MPI_COMM_WORLD, &status);
		answer += temp_answer;
		heavyParams[1]++;
		if (heavyParams[1] == N) {
			heavyParams[0]++;
			heavyParams[1] = 0;
		}
		if (heavyParams[0] == N) {
			MPI_Send(terminateParams, 2, MPI_INT, status.MPI_SOURCE, tag,
			MPI_COMM_WORLD);
			terminated++;
		} else {
			MPI_Send(heavyParams, 2, MPI_INT, status.MPI_SOURCE, tag,
			MPI_COMM_WORLD);
		}
	} while (terminated < numprocs - 1);
	return answer;
}

void dynamic_slave(int *heavyParams, int tag, MPI_Status status) {
	double answer = 0;
	int terminate = 0;
	while (!terminate) {
		MPI_Recv(heavyParams, 2, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		if (heavyParams[0] == -1 || heavyParams[1] == -1) {
			terminate = 1;
		} else {
			answer = heavy(heavyParams[0], heavyParams[1]);
			MPI_Send(&answer, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
		}
	}
}

double parallel_heavy_using_dynamic_approach(int myid, int N, int numprocs,
		int tag, MPI_Status status) {
	int heavyParams[2] = { 0, -1 }; // index 0 for x, index 1 for y
	if (myid == 0) {
		return dynamic_master(N, numprocs, heavyParams, tag, status);
	} else {
		dynamic_slave(heavyParams, tag, status);
		return -1;
	}

}

int main(int argc, char *argv[]) {
	int myid, numprocs, tag = 0, N = 20;
	double answer, begin, end;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	srand(time(0));

	begin = MPI_Wtime();
	if (numprocs == 1) {
		answer = sequential_approach(N);
	} else if (numprocs > 1) { 		// Insert in a comment the line of the approach you don't want to check
		answer = parallel_heavy_using_static_approach(myid, N, numprocs, tag, status);
		answer = parallel_heavy_using_dynamic_approach(myid, N, numprocs, tag, status);
	}
	end = MPI_Wtime();

	if (myid == 0) {
		printf("answer = %e\n", answer); 	// N = 20 correct answer = 8.354289e+06
		printf("%e\n", end-begin);
	}
	MPI_Finalize();
	return 0;
}
