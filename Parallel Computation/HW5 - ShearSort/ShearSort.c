#include "ShearSort.h"

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "OddEvenSort.h"

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Not Enough arguments");
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
	int size, matSize, dim[CART_SIZE], coord[CART_SIZE], period[CART_SIZE] = { 0 },
			reorder = 0;

	Proc proc;

	MPI_Comm comm;
	MPI_Datatype MPICuboid;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc.rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	matSize = validateSize(size);

	Cuboid cuboids[size];

	if (proc.rank == MASTER) {
		readFile(argv[1], cuboids, size);
	}

	createDataTypeForCuboid(proc.cuboid, &MPICuboid);

	// Distribute 1 cuboid element for 1 process
	MPI_Scatter(cuboids, 1, MPICuboid, &proc.cuboid, 1, MPICuboid, MASTER,
			MPI_COMM_WORLD);

	proc.cuboid.vol = proc.cuboid.length * proc.cuboid.width * proc.cuboid.height;

	createCart(&proc, matSize, dim, period, reorder, coord, &comm);

	shearSort(cuboids, MPICuboid, matSize, &proc, comm, coord);


	MPI_Gather(&proc.cuboid, 1, MPICuboid, cuboids, 1, MPICuboid, MASTER, MPI_COMM_WORLD);

	if (proc.rank == MASTER) {
		writeFile(argv[2], cuboids, size, matSize);
	}

	fflush(stdout);
	MPI_Finalize();
	return 0;

}

int validateSize(int size) {
	int matSize = sqrt(size);
	if (size != (matSize * matSize)) {
		fprintf(stderr, "The number of process must have an integer square root");
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
	return matSize;
}

void readFile(char *filename, Cuboid* cuboids, int size) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		fprintf(stderr, "Could not open file: %s\n", filename);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
	for (int i = 0; i < size; ++i) {
		if (fscanf(file, "%d%f%f%f", &cuboids[i].id, &cuboids[i].length,
				&cuboids[i].width, &cuboids[i].height) != 4) {
			fprintf(stderr, "line %d: Cannot read from file.", __LINE__);
			MPI_Abort(MPI_COMM_WORLD, 1);
		}
	}
	fclose(file);
}

void writeFile(char *filename, Cuboid cuboids[], int size, int matSize) {
	FILE *file = fopen(filename, "w+t");
	if (!file) {
		fprintf(stderr, "Could not open file: %s\n", filename);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
	for (int i = 0; i < matSize; ++i) {
		for (int j = (i % 2 == 0 ? 0 : matSize-1); (i % 2 == 0 ? j < matSize : j >= 0); (i % 2 == 0 ? ++j : --j)) {
			fprintf(file, "%d\n",(*(cuboids + i * matSize + j)).id);
		}
	}
	fclose(file);
}

void createDataTypeForCuboid(Cuboid myCuboid, MPI_Datatype *MPICuboid) {
	MPI_Datatype type[5] =
			{ MPI_INT, MPI_FLOAT, MPI_FLOAT, MPI_FLOAT, MPI_FLOAT };
	int blocklen[5] = { 1, 1, 1, 1, 1 };
	MPI_Aint disp[5];
	disp[0] = (char*) &myCuboid.id - (char*) &myCuboid;
	disp[1] = (char*) &myCuboid.length - (char*) &myCuboid;
	disp[2] = (char*) &myCuboid.width - (char*) &myCuboid;
	disp[3] = (char*) &myCuboid.height - (char*) &myCuboid;
	disp[4] = (char*) &myCuboid.vol - (char*) &myCuboid;
	MPI_Type_create_struct(5, blocklen, disp, type, MPICuboid);
	MPI_Type_commit(MPICuboid);
}

void createCart(Proc *proc, int matSize, int *dim, int *period, int reorder,
		int *coord, MPI_Comm* comm) {
	dim[0] = matSize;
	dim[1] = matSize;
	MPI_Cart_create(MPI_COMM_WORLD, CART_SIZE, dim, period, reorder, comm);
	MPI_Cart_coords(*comm, proc->rank, CART_SIZE, coord);
}

void shearSort(Cuboid *cuboids, MPI_Datatype MPICuboid, int matSize, Proc *proc,
		MPI_Comm comm, int *coord) {

	int totalIterations = (int) ceil(2 * log2((double) (matSize))) + 1;
	for (int i = 0; i < totalIterations; ++i) {
		oddEvenSort(matSize, coord, proc, ROWS, comm, MPICuboid);
		oddEvenSort(matSize, coord, proc, COLS, comm, MPICuboid);
	}
}

void oddEvenSort(int matSize, int *coord, Proc *proc, PassDirection passDir,
		MPI_Comm comm, MPI_Datatype MPICuboid) {
	int neighbor1, neighbor2, neigborRankForExchange;
	CommDirection commDir;
	SortDirection sortDir = getSortDirection(coord, passDir);
	MPI_Cart_shift(comm, passDir, 1, &neighbor1, &neighbor2);

	for (int i = 0; i < matSize; ++i) {
		commDir = getCommDirection(coord, i, passDir);
		neigborRankForExchange = (commDir == SEND ? neighbor2 : neighbor1);

		if (neigborRankForExchange != MPI_PROC_NULL) {
			exchangeWithNeighbor(proc, commDir, sortDir, neigborRankForExchange, comm, MPICuboid);
		}
	}
}

void exchangeWithNeighbor(Proc* proc, CommDirection commDir, SortDirection sortDir, int neighborRank, MPI_Comm comm, MPI_Datatype MPICuboid) {
	MPI_Status status;
	Cuboid cuboid;
	if (commDir == SEND) {
		MPI_Send(&proc->cuboid, 1, MPICuboid, neighborRank, 0, comm);
		MPI_Recv(&cuboid, 1, MPICuboid, neighborRank, 0, comm, &status);
	} else {
		MPI_Recv(&cuboid, 1, MPICuboid, neighborRank, 0, comm, &status);
		MPI_Send(&proc->cuboid, 1, MPICuboid, neighborRank, 0, comm);
	}
	if (comapreCuboids(proc->cuboid, cuboid, sortDir) == (commDir == SEND ? -1 : 1)) {
		proc->cuboid = cuboid;
	}
}

CommDirection getCommDirection(int *coord, int i, PassDirection dir) {
	return (i % 2 == coord[dir] % 2 ? SEND : RECIEVE);
}

SortDirection getSortDirection(int *coord, PassDirection dir) {
	if (dir == COLS) {
		return ASCENDING;
	}
	return (SortDirection) (coord[0] % 2);
}

int comapreCuboids(Cuboid x, Cuboid y, SortDirection sortDir) {
	int res = -1;
	if (sortDir == ASCENDING) {
		if (x.vol < y.vol) {
			res = 1;
		} else if (x.vol == y.vol) {
			res = (x.height < y.height ?
										1 : (x.height > y.height ? -1 : 0));
		}
	} else {
		if (x.vol > y.vol) {
			res = 1;
		} else if (x.vol == y.vol) {
			res = (x.height > y.height ?
					1 : (x.height < y.height ? -1 : 0));
		}
	}
	return res;
}
