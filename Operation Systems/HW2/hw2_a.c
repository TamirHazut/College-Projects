#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hw2_a.h"
#include "general.h"

int validArrayForThreadsWithoutMutex[NUM_OF_TASKS] = { 0 };
int sudoku_board[SIZE * SIZE];

void get_board_for_threads(int argc, char* argv[]) {
	if (argc == 1) {
		int* board_from_user = read_board_from_user();
		memcpy(sudoku_board, board_from_user, sizeof(int) * SIZE * SIZE);
		start_threads_without_mutex("manual solution");
		free(board_from_user);
	} else {
		memcpy(sudoku_board, read_board_from_file(argv[1]),
				sizeof(int) * SIZE * SIZE);
		start_threads_without_mutex(argv[1]);
	}
}

void start_threads_without_mutex(char* filename) {
	pthread_t threads_handlers[NUM_OF_THREADS_WITHOUT_MUTEX];
	int i, j, threadIndex = 0;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (i % 3 == 0 && j % 3 == 0) {
				Indexes* matrixIndexes = (Indexes*) malloc(sizeof(Indexes));
				matrixIndexes->row = i;
				matrixIndexes->column = j;
				pthread_create(&threads_handlers[threadIndex++], NULL,
						isValidMatrix, (void*) matrixIndexes);
			}
			if (i == 0) {
				Indexes* columnIndexes = (Indexes*) malloc(sizeof(Indexes));
				columnIndexes->row = i;
				columnIndexes->column = j;
				pthread_create(&threads_handlers[threadIndex++], NULL,
						isValidColumn, (void*) columnIndexes);

			}
			if (j == 0) {
				Indexes* rowIndexes = (Indexes*) malloc(sizeof(Indexes));
				rowIndexes->row = i;
				rowIndexes->column = j;
				pthread_create(&threads_handlers[threadIndex++], NULL,
						isValidRow, (void*) rowIndexes);
			}
		}
	}
	for (i = 0; i < NUM_OF_THREADS_WITHOUT_MUTEX; i++) {
		pthread_join(threads_handlers[i], NULL);
	}
	checkValidArray(validArrayForThreadsWithoutMutex, filename);
}

void *isValidRow(void* args) {
	Indexes* params = (Indexes*) args;
	int row = params->row;
	if (params->column != 0 || row >= SIZE) {
		pthread_exit(NULL);
	}
	validArrayForThreadsWithoutMutex[row] = checkForValidRow(sudoku_board, row);
	pthread_exit(NULL);
}

void *isValidColumn(void* args) {
	Indexes* params = (Indexes*) args;
	int column = params->column;
	if (params->row != 0 || column >= SIZE) {
		pthread_exit(NULL);
	}
	validArrayForThreadsWithoutMutex[column + SIZE] = checkForValidColumn(
			sudoku_board, column);
	pthread_exit(NULL);
}

void *isValidMatrix(void* args) {
	Indexes* params = (Indexes*) args;
	int row = params->row;
	int column = params->column;
	if (column % 3 != 0 || column > 6 || row % 3 != 0 || row > 6) {
		pthread_exit(NULL);
	}
	validArrayForThreadsWithoutMutex[row + column / 3 + SIZE * 2] =
			checkForValidMatrix(sudoku_board, row, column);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	get_board_for_threads(argc, argv);
	return EXIT_SUCCESS;
}

