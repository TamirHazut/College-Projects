#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "general.h"

int* read_board_from_user() {
	int* board = (int*) calloc(SIZE * SIZE, sizeof(int));
	if (!board) {
		return NULL;
	}
	int i, num;
	printf(
			"Please enter your solution according to the rows (Integers between 1-9):\n");
	for (i = 0; i < SIZE * SIZE; i++) {
		scanf("%d", &num);
		if (num >= 1 && num <= 9) {
			*(board + i) = num;
		} else {
			*(board + i) = DEFAULT_VAULE;
		}
	}
	return board;
}

void read_board_from_file(char* filename, int* board) {
	int num, index = 0;
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("An error occurd and file: %s could not be open\n", filename);
	} else {
		fscanf(fp, "%d", &num);
		while (num != EOF && index < SIZE * SIZE) {
			board[index] = num;
			index++;
			fscanf(fp, "%d", &num);
		}
		fclose(fp);
	}
}

int checkForValidRows(int* sudoku_board) {
	int i;
	for (i = 0; i < SIZE; i++) {
		if (!checkForValidRow(sudoku_board, i)) {
			return 0;
		}
	}
	return 1;
}

int checkForValidRow(int* sudoku_board, int row) {
	int i, valid[SIZE];
	fillArray(valid, SIZE);
	for (i = 0; i < SIZE; i++) {
		if (valid[*(sudoku_board + row * SIZE + i) - 1] == 1) {
			return 0;
		}
		valid[*(sudoku_board + row * SIZE + i) - 1] = 1;
	}
	return 1;
}
int checkForValidColumns(int* soduku_board) {
	int i;
	for (i = 0; i < SIZE; i++) {
		if (!checkForValidColumn(soduku_board, i)) {
			return 0;
		}
	}
	return 1;
}

int checkForValidColumn(int* sudoku_board, int col) {
	int i, valid[SIZE];
	fillArray(valid, SIZE);
	for (i = 0; i < SIZE; i++) {
		if (valid[*(sudoku_board + i * SIZE + col) - 1] == 1) {
			return 0;
		}
		valid[*(sudoku_board + i * SIZE + col) - 1] = 1;
	}
	return 1;
}
int checkForValidMatrices(int* soduku_board) {
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
int checkForValidMatrix(int* sudoku_board, int row, int col) {
	int i, j, len, valid[SIZE];
	len = sqrt(SIZE);
	fillArray(valid, SIZE);
	for (i = row; i < row + len; i++) {
		for (j = col; j < col + len; j++) {
			if (valid[*(sudoku_board + i * SIZE + j) - 1] == 1) {
				return 0;
			}
			valid[*(sudoku_board + i * SIZE + j) - 1] = 1;
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
