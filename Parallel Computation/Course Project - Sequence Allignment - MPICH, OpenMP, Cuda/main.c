#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "GeneralFunc.h"
#include "CudaFunc.h"

int main(int argc, char **argv) {
	int rank, size, sequencesToCompare, offsetTasks, i;
	FILE *inputFile, *outputFile;
	ScoreWeight scoreWeight;
	Sequence sequence1, *sequences;
	BestMatch *bestMatch;
	float *compareTable;
	MPI_Status status;

	if (argc != 2) {
		fprintf(stderr,
				"Missing args, Run command: 'make run FILE=<filename>'\n");
		MPI_Abort(MPI_COMM_WORLD, __LINE__);
	}

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (size != 2) {
		fprintf(stderr, "This program can be run with only two processes\n");
		MPI_Abort(MPI_COMM_WORLD, __LINE__);
	}

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// only 1 process can read/write to files
	if (rank == 0) {
		inputFile = openFile(argv[1], "r");
		outputFile = openFile(OUTPUT_FILE, "w");

		// Reading and sending the score weight to the other process
		scoreWeight = readWeightFromFile(inputFile);
		MPI_Send(&scoreWeight.w1, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&scoreWeight.w2, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&scoreWeight.w3, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&scoreWeight.w4, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);

		// Reading and sending the main sequence to the other process
		sequence1 = readSequenceFromFile(inputFile, 1);
		MPI_Send(&sequence1.length, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(sequence1.seq, sequence1.length, MPI_CHAR, 1, 0,
		MPI_COMM_WORLD);

		// Reading the number of sequences for comparison
		sequencesToCompare = readNumberOfSequencesToComapre(inputFile);
		MPI_Send(&sequencesToCompare, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	} else {
		// Receive the score weight
		MPI_Recv(&scoreWeight.w1, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&scoreWeight.w2, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&scoreWeight.w3, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&scoreWeight.w4, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);

		// Receive the main sequence
		MPI_Recv(&sequence1.length, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		sequence1.seq = (char*) malloc(sizeof(char) * sequence1.length);
		if (!sequence1.seq) {
			fprintf(stderr, "Rank %d: Could not allocate sequence1.seq\n",
					rank);
			MPI_Abort(MPI_COMM_WORLD, __LINE__);
		}
		MPI_Recv(sequence1.seq, sequence1.length, MPI_CHAR, 0, 0,
		MPI_COMM_WORLD, &status);

		// Receiving the number of sequences for comparison
		MPI_Recv(&sequencesToCompare, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
				&status);
	}

	compareTable = createCompareTable(scoreWeight);

	// Allocating space for sequences to each process
	sequences = (Sequence*) malloc(sizeof(Sequence) * sequencesToCompare);
	if (!sequences) {
		fprintf(stderr, "Rank %d: Could not allocate sequences\n", rank);
		MPI_Abort(MPI_COMM_WORLD, __LINE__);
	}

	// Allocating space for results to each process
	bestMatch = (BestMatch*) malloc(sizeof(BestMatch) * sequencesToCompare);
	if (!bestMatch) {
		fprintf(stderr, "Rank %d: Could not allocate bestMatch\n", rank);
		MPI_Abort(MPI_COMM_WORLD, __LINE__);
	}

	for (i = 0; i < sequencesToCompare; ++i) {
		if (rank == 0) {
			// Reading and sending the rest of the sequences to the other process
			sequences[i] = readSequenceFromFile(inputFile, 0);
			MPI_Send(&sequences[i].length, 1, MPI_INT, 1, 0,
			MPI_COMM_WORLD);
			MPI_Send(sequences[i].seq, sequences[i].length, MPI_CHAR, 1, 0,
			MPI_COMM_WORLD);
		} else {
			//Receiving the sequence that needs to be compare
			MPI_Recv(&(sequences[i].length), 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
					&status);
			sequences[i].seq = (char*) malloc(
					sizeof(char) * sequences[i].length);
			if (!sequences[i].seq) {
				fprintf(stderr,
						"Rank %d: Could not allocate sequences[%d].seq\n", rank,
						i);
				MPI_Abort(MPI_COMM_WORLD, __LINE__);
			}
			MPI_Recv(sequences[i].seq, sequences[i].length, MPI_CHAR, 0, 0,
			MPI_COMM_WORLD, &status);
		}

		// Each process checks his sequences based on the offset indexes given
		offsetTasks = ((sequence1.length - sequences[i].length) / 2) + 1;
		if (rank == 0) {
			bestMatch[i] = findBestMatchingComparison(sequence1, sequences[i], compareTable,
					0, offsetTasks, scoreWeight);
		} else {
			bestMatch[i] = findBestMatchingComparison(sequence1, sequences[i], compareTable,
					offsetTasks, sequence1.length - sequences[i].length + 1,
					scoreWeight);
		}
	}
	for (i = 0; i < sequencesToCompare; i++) {
		if (rank == 0) {
			// Receiving the other process results
			BestMatch temp;
			MPI_Recv(&temp.offset, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
			MPI_Recv(&temp.mutantIndex, 1, MPI_INT, 1, 0, MPI_COMM_WORLD,
					&status);
			MPI_Recv(&temp.score, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);

			// Comparing the results of both process and writing the best one
			writeToFileComparisonResult(outputFile,
					(temp.score <= bestMatch[i].score ? bestMatch[i] : temp));

		} else {
			// Sending the other process results
			MPI_Send(&bestMatch[i].offset, 1, MPI_INT, 0, 0,
			MPI_COMM_WORLD);
			MPI_Send(&bestMatch[i].mutantIndex, 1, MPI_INT, 0, 0,
			MPI_COMM_WORLD);
			MPI_Send(&bestMatch[i].score, 1, MPI_DOUBLE, 0, 0,
			MPI_COMM_WORLD);
		}
	}

	// Freeing allocated memory and closing the opened files
	if (rank == 0) {
		fclose(inputFile);
		fclose(outputFile);
	}
	for (i = 0; i < sequencesToCompare; i++) {
		free(sequences[i].seq);
	}
	free(sequences);
	free(sequence1.seq);
	free(bestMatch);
	free(compareTable);
	MPI_Finalize();
	return EXIT_SUCCESS;
}


