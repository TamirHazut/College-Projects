#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

#include "v2.h"
#include "general.h"

Shared_Struct_For_Processes** open_mmap(int num_of_boards) {
	Shared_Struct_For_Processes** shared_sudokus =
			(Shared_Struct_For_Processes**) malloc(
					sizeof(Shared_Struct_For_Processes*) * num_of_boards);
	if ((!shared_sudokus)) {
		perror("malloc");
		return NULL;
	}

	shared_sudokus = (Shared_Struct_For_Processes**) mmap(NULL,
			sizeof(shared_sudokus), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_SHARED, -1, 0);
	if (shared_sudokus == MAP_FAILED) {
		perror("mmap");
		return NULL;
	}
	return shared_sudokus;
}

void close_mmap(Shared_Struct_For_Processes** shared_sudokus, int num_of_boards) {
	int i;
	for (i = 0; i < num_of_boards; i++) {
		munmap(shared_sudokus[i], sizeof(Shared_Struct_For_Processes));
	}
	munmap(shared_sudokus, sizeof(shared_sudokus));
}

void create_child_processes(char *argv[],
		Shared_Struct_For_Processes** shared_sudokus, int num_of_boards) {
	int i;

	create_fork_for_mmap(shared_sudokus, num_of_boards, ROWS);
	create_fork_for_mmap(shared_sudokus, num_of_boards, COLUMNS);
	create_fork_for_mmap(shared_sudokus, num_of_boards, MATRICES);

	for (i = 0; i < num_of_boards; i++) {
		int result = 0;
		result += shared_sudokus[i]->status[0];
		result += shared_sudokus[i]->status[1];
		result += shared_sudokus[i]->status[2];
		printf("%s is %s\n", (!argv[i + 1] ? "manual solution" : argv[i + 1]),
				(result == 3 ? "legal" : "not legal"));
	}
}

void check_solution(Shared_Struct_For_Processes* shared_sudoku, int whatToCheck) {
	switch (whatToCheck) {
	case ROWS:
		shared_sudoku->status[0] = checkForValidRows(shared_sudoku->solution);
		break;
	case COLUMNS:
		shared_sudoku->status[1] = checkForValidColumns(
				shared_sudoku->solution);
		break;
	case MATRICES:
		shared_sudoku->status[2] = checkForValidMatrices(
				shared_sudoku->solution);
		break;
	}
}

void create_fork_for_mmap(Shared_Struct_For_Processes** shared_sudokus,
		int num_of_boards, int whatToCheck) {
	int pid = fork(), i;
	if (pid < 0) {
		perror("fork");
		exit(-1);
	} else if (pid == 0) {
		for (i = 0; i < num_of_boards; i++) {
			check_solution(shared_sudokus[i], whatToCheck);
		}
		exit(EXIT_SUCCESS);
	} else {
		wait(NULL);
	}
}

void get_boards_for_processes(int argc, char* argv[]) {
	int i, num_of_boards = (argc - 1 == 0 ? 1 : argc - 1);
	Shared_Struct_For_Processes** shared_sudokus = open_mmap(num_of_boards);
	if (!shared_sudokus) {
		exit(-1);
	}

	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			shared_sudokus[i - 1] = (Shared_Struct_For_Processes*) malloc(
					sizeof(Shared_Struct_For_Processes));
			if (!shared_sudokus[i - 1]) {
				perror("malloc");
				exit(-1);
			}
			shared_sudokus[i - 1] = mmap(NULL,
					sizeof(Shared_Struct_For_Processes), PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_SHARED, -1, 0);
			if (shared_sudokus[i - 1] == MAP_FAILED) {
				perror("mmap");
				exit(-1);
			}
			memcpy(shared_sudokus[i - 1]->solution,
					read_board_from_file(argv[i]), sizeof(int) * SIZE * SIZE);
		}
	} else {
		shared_sudokus[0] = (Shared_Struct_For_Processes*) malloc(
				sizeof(Shared_Struct_For_Processes));
		if (!shared_sudokus[0]) {
			perror("malloc");
			exit(-1);
		}
		shared_sudokus[0] = mmap(NULL, sizeof(Shared_Struct_For_Processes),
		PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_SHARED, -1, 0);
		if (shared_sudokus[0] == MAP_FAILED) {
			perror("mmap");
			exit(-1);
		}
		memcpy(shared_sudokus[0]->solution, read_board_from_user(),
				sizeof(int) * SIZE * SIZE);
	}
	create_child_processes(argv, shared_sudokus, num_of_boards);
	close_mmap(shared_sudokus, num_of_boards);
}

int main(int argc, char* argv[]) {
	get_boards_for_processes(argc, argv);
	return EXIT_SUCCESS;
}
