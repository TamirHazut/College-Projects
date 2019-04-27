#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "checksudokumatrices.h"

int main(int argc, char* argv[]) {
	int valid = 0, fd = atoi(argv[1]);
	if (argc > 2) {
		int *board = get_board_from_string(argv[2]);
		valid = checkForValidMatrices(board);

		char* temp = malloc(sizeof(char) * 2);
		if (!temp) {
			return EXIT_FAILURE;
		}
		sprintf(temp, "%d", valid);
		write(fd, temp, sizeof(char));
		free(temp);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int* get_board_from_string(char temp[SIZE * SIZE]) {
	int i;
	int* board = malloc(sizeof(int) * SIZE * SIZE);
	if (!board) {
		return NULL;
	}
	for (i = 0; i < SIZE * SIZE; i++) {
		board[i] = temp[i] - 48;
	}
	return board;
}

int checkForValidMatrices(const int* soduku_board) {
	int i, j;
	for (i = 0; i < SIZE; i += 3) {
		for (j = 0; j < SIZE; j += 3) {
			if (!checkForValidMatrix(soduku_board, i, j)) {
				return 0;
			}
		}
	}
	return 1;
}
int checkForValidMatrix(const int* sudoku_matrix, int row, int col) {
	int i, j, len, valid[SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	len = sqrt(SIZE);
//	fillArray(valid, SIZE);
	for (i = row; i < row + len; i++) {
		for (j = col; j < col + len; j++) {
			if (valid[*(sudoku_matrix + i * SIZE + j) - 1] == 1) {
				return 0;
			}
			valid[*(sudoku_matrix + i * SIZE + j) - 1] = 1;
		}
	}
	return 1;
}

void fillArray(int* arr, int length) {
	int i;
	for (i = 0; i < length; i++) {
		arr[i] = 0;
	}
}
