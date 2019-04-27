#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "checksudokurows.h"

int main(int argc, char* argv[]) {
	int valid = 0, fd = atoi(argv[1]);
	if (argc > 2) {
		int *board = get_board_from_string(argv[2]);
		valid = checkForValidRows(board);

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

int checkForValidRows(const int* sudoku_board) {
	int i;
	for (i = 0; i < SIZE; i++) {
		if (!checkForValidRow(sudoku_board, i)) {
			return 0;
		}
	}
	return 1;
}

int checkForValidRow(const int* sudoku_row, int row) {
	int i, valid[SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//	fillArray(valid, SIZE);
	for (i = 0; i < SIZE; i++) {
		if (valid[*(sudoku_row + row * SIZE + i) - 1] == 1) {
			return 0;
		}
		valid[*(sudoku_row + row * SIZE + i) - 1] = 1;
	}
	return 1;
}

void fillArray(int* arr, int length) {
	int i;
	for (i = 0; i < length; i++) {
		arr[i] = 0;
	}
}
