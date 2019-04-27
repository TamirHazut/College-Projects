#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

#include "hw1.h"

void get_board_for_processes(int argc, char* argv[]) {
	Shared_Struct_For_Processes sudoku;
	if (argc == 1) {
		int* board_from_user = read_board_from_user();
		memcpy(sudoku.solution, board_from_user, sizeof(int)*SIZE*SIZE);
		check_solution_using_pipe(sudoku.solution, "STDIN");
		split_work_using_mmap(&sudoku, "STDIN");
		free(board_from_user);
	} else {
		int i;
		for (i = 1; i < argc; i++) {
			read_board_from_file(argv[i], sudoku.solution);
			check_solution_using_pipe(sudoku.solution, argv[i]);
			split_work_using_mmap(&sudoku, argv[i]);
		}
	}
}

void split_work_using_mmap(Shared_Struct_For_Processes* sudoku, char* filename) {
	Shared_Struct_For_Processes *shared_sudoku = (Shared_Struct_For_Processes*) mmap(NULL, sizeof(Shared_Struct_For_Processes),
	PROT_READ | PROT_WRITE,
	MAP_ANON | MAP_SHARED, -1, 0);
	memcpy(shared_sudoku, sudoku, sizeof(Shared_Struct_For_Processes));
	check_solution_using_mmap(shared_sudoku, filename);
	munmap(shared_sudoku, sizeof(Shared_Struct_For_Processes));
}

void check_solution_using_mmap(Shared_Struct_For_Processes* shared_sudoku, char* filename) {
	int pid1, pid2, pid3;
	if (!(pid1 = fork())) {
		shared_sudoku->status[0] = checkForValidRows(shared_sudoku->solution);
	} else if (!(pid2 = fork())) {
		shared_sudoku->status[1] = checkForValidColumns(
				shared_sudoku->solution);
	} else if (!(pid3 = fork())) {
		shared_sudoku->status[2] = checkForValidMatrices(
				shared_sudoku->solution);
	} else {
		wait(NULL);
		wait(NULL);
		wait(NULL);
		printf("%s is %s\n", filename,
				(!shared_sudoku->status[0] || !shared_sudoku->status[1]
						|| !shared_sudoku->status[2] ? "Illegal" : "Legal"));
	}
}

char* create_writing_channel(int pfd[]) {
	char* writeChannel = malloc(sizeof(char) * 2);
	if (pipe(pfd) < -0) {
		perror("pipe");
		return NULL;
	}
	sprintf(writeChannel, "%d\n", pfd[1]);
	return writeChannel;
}

void create_fork_for_pipe(int pfd[], char* newargv[], char* newenviron[]) {
	int pid = -1;
	if ((pid = fork()) < 0) {
		perror("fork");
	} else if (pid > 0) {
	} else {
		close(pfd[0]);
		execve(newargv[0], newargv, newenviron);
	}
}
char* convert_board_to_string(int board[]) {
	int i;
	char* temp = malloc(sizeof(char) * SIZE * SIZE);
	for (i = 0; i < SIZE * SIZE; i++) {
		sprintf(&temp[i], "%d", board[i]);
	}
	return temp;
}

void check_solution_using_pipe(int* board, char* filename) {
	char temp[2], *newenviron[] = { NULL };
	int pfd1[2], pfd2[2], pfd3[2], status[3] = { 0, 0, 0 };
	char* board_as_string = convert_board_to_string(board);

	char* writeChannel1 = create_writing_channel(pfd1);
	char* writeChannel2 = create_writing_channel(pfd2);
	char* writeChannel3 = create_writing_channel(pfd3);
	if ((!writeChannel1) || (!writeChannel2) || (!writeChannel3)) {
		return;
	}

	char *newargv1[] = { "./CheckSudokuRows", writeChannel1, board_as_string,
	NULL };
	char *newargv2[] = { "./CheckSudokuColumns", writeChannel2, board_as_string,
	NULL };
	char *newargv3[] = { "./CheckSudokuMatrices", writeChannel3,
			board_as_string, NULL };
	create_fork_for_pipe(pfd1, newargv1, newenviron);
	create_fork_for_pipe(pfd2, newargv2, newenviron);
	create_fork_for_pipe(pfd3, newargv3, newenviron);

	wait(NULL);
	wait(NULL);
	wait(NULL);
	close(pfd1[1]);
	close(pfd2[1]);
	close(pfd3[1]);
	read(pfd1[0], temp, sizeof(char));
	status[0] = atoi(temp);
	read(pfd2[0], temp, sizeof(char));
	status[1] = atoi(temp);
	read(pfd3[0], temp, sizeof(char));
	status[2] = atoi(temp);
	printf("%s is %s\n", filename,
			(!status[0] || !status[1] || !status[2] ? "Illegal" : "Legal"));
	free(board_as_string);
	close(pfd1[0]);
	close(pfd2[0]);
	close(pfd3[0]);

}
