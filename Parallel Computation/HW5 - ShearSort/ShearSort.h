#ifndef SHEARSORT_H_
#define SHEARSORT_H_
#include <mpi.h>

#define CART_SIZE 2

#define MASTER 0

typedef enum {
	COLS, ROWS
} PassDirection;

typedef enum {
	ASCENDING, DESCENDING
} SortDirection;

typedef enum {
	RECIEVE, SEND
} CommDirection;

typedef struct {
	int id;
	float length;
	float width;
	float height;
	float vol;
} Cuboid;

typedef struct {
	int rank;
	int procLeftId;
	int procRightId;
	Cuboid cuboid;
} Proc;

SortDirection getSortDirection(int *coord, PassDirection dir);
CommDirection getCommDirection(int *coord, int i, PassDirection dir);

int comapreCuboids(Cuboid x, Cuboid y, SortDirection sortDir);

int validateSize(int size);
void readFile(char *filename, Cuboid *cuboids, int size);
void writeFile(char *filename, Cuboid cuboids[], int size, int matSize);
void createDataTypeForCuboid(Cuboid myCuboid, MPI_Datatype *MPICuboid);
void createCart(Proc *proc, int matSize, int *dim, int *period, int reorder,
		int *coord, MPI_Comm *comm);

void shearSort(Cuboid *cuboids, MPI_Datatype MPICuboid, int matSize, Proc *proc,
		MPI_Comm comm, int *coord);
void oddEvenSort(int matSize, int *coord, Proc *proc, PassDirection passDir,
		MPI_Comm comm, MPI_Datatype MPICuboid);
void exchangeWithNeighbor(Proc *proc, CommDirection commDir,
	SortDirection sortDir, int neighborRank, MPI_Comm comm,
	MPI_Datatype MPICuboid);

#endif /* SHEARSORT_H_ */
