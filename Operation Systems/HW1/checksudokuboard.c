#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "checksudokuboard.h"
#include "general.h"

int main(int argc, char* argv[]) {
	int i, num_of_boards, *board;
	char num_of_boards_as_string;
	if (argc != 2) {
		perror("invalid params");
		exit(-1);
	}
	char *result = (char*) malloc(sizeof(char) * 2);
	if (!result) {
		perror("malloc");
		exit(-1);
	}

	if (read(STDIN_FILENO, &num_of_boards_as_string, sizeof(char)) == -1) {
		perror("read");
		exit(-1);
	}

	char* board_as_string = (char*) malloc(sizeof(char) * SIZE * SIZE);
	if (!board_as_string) {
		perror("malloc");
		exit(-1);
	}
	num_of_boards = atoi(&num_of_boards_as_string);

	for (i = 0; i < num_of_boards; i++) {
		if (read(STDIN_FILENO, board_as_string, sizeof(char) * SIZE * SIZE)
				== -1) {
			perror("read");
			exit(-1);
		}
		board = convert_board_from_string(board_as_string);
		sprintf(result, "%d", check_board(board, argv[1]));
		if (write(STDOUT_FILENO, result, sizeof(char)) == -1) {
			perror("write");
			exit(-1);
		}
	}
	return EXIT_SUCCESS;
}

int check_board(int* board, char* checkSymbol) {
	int result = 0;
	if (!strcmp(checkSymbol, "-r")) {
		result = checkForValidRows(board);
	} else if (!strcmp(checkSymbol, "-c")) {
		result = checkForValidColumns(board);
	} else if (!strcmp(checkSymbol, "-m")) {
		result = checkForValidMatrices(board);
	} else {
		perror("invalid params");
		exit(-1);
	}
	return result;
}
