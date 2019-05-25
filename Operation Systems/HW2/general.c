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

int* read_board_from_file(char* filename) {
	int num, index = 0, *board = (int*) malloc(sizeof(int) * SIZE * SIZE);
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("An error occurd and file: %s could not be open\n", filename);
		return NULL;
	} else {
		fscanf(fp, "%d", &num);
		while (num != EOF && index < SIZE * SIZE) {
			board[index] = num;
			index++;
			fscanf(fp, "%d", &num);
		}
		fclose(fp);
		return board;
	}
}

int checkForValidRow(int* sudoku_board, int row) {
	int i, valid[SIZE] = { 0 };
	for (i = 0; i < SIZE; i++) {
		if (valid[*(sudoku_board + row * SIZE + i) - 1] == 1) {
			return 0;
		}
		valid[*(sudoku_board + row * SIZE + i) - 1] = 1;
	}
	return 1;
}

int checkForValidColumn(int* sudoku_board, int col) {
	int i, valid[SIZE] = { 0 };
	for (i = 0; i < SIZE; i++) {
		if (valid[*(sudoku_board + i * SIZE + col) - 1] == 1) {
			return 0;
		}
		valid[*(sudoku_board + i * SIZE + col) - 1] = 1;
	}
	return 1;
}

int checkForValidMatrix(int* sudoku_board, int row, int col) {
	int i, j, len, valid[SIZE] = { 0 };
	len = sqrt(SIZE);
	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			if (valid[*(sudoku_board + (row + i) * SIZE + (col + j)) - 1]
					== 1) {
				return 0;
			}
			valid[*(sudoku_board + (row + i) * SIZE + (col + j)) - 1] = 1;
		}
	}
	return 1;
}

void checkValidArray(int* validArray, char* filename) {
	int i;
	for (i = 0; i < NUM_OF_TASKS; i++) {
		if (validArray[i] == 0) {
			printf("%s is not legal\n", filename);
			return;
		}
	}
	printf("%s is legal\n", filename);
}

