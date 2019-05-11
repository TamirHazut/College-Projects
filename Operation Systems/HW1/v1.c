#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "v1.h"
#include "general.h"

void change_pipe_fd_channel(int *pfd) {
	if (dup2(pfd[0], STDIN_FILENO) == -1) {
		perror("dup2 stdin");
		exit(-1);
	}
	if (dup2(pfd[1], STDOUT_FILENO) == -1) {
		perror("dup2 stdout");
		exit(-1);
	}
	close(pfd[0]);
	close(pfd[1]);
}

void create_fork_for_pipe(char* boards_as_string, int num_of_boards, int *pfd,
		char* newargv[], int* childResults) {
	int pid = fork();
	if (pid < 0) {
		perror("fork");
	} else if (pid == 0) {
		change_pipe_fd_channel(pfd);
		close(pfd[0]);
		close(pfd[1]);
		execv(newargv[0], newargv);
		perror("execve");
	} else {
		write(pfd[1], boards_as_string, strlen(boards_as_string));
		close(pfd[1]);
		wait(NULL);

		check_solution_using_pipe(num_of_boards, pfd, childResults);

		if (dup2(STDOUT_FILENO, pfd[1]) == -1) {
			perror("dup2 pfd[1]");
			exit(-1);
		}
		close(pfd[0]);
	}
}

void check_solution_using_pipe(int num_of_boards, int *pfd, int* childResults) {
	int i;
	char current_result;
	for (i = 0; i < num_of_boards; i++) {
		read(pfd[0], &current_result, sizeof(char));
		childResults[i] = atoi(&current_result);
	}
	if (dup2(STDOUT_FILENO, pfd[1]) == -1) {
		perror("dup2 stdout");
		exit(-1);
	}
	close(pfd[1]);
}

void create_child_processes(char* argv[], char* boards_as_string,
		int num_of_boards, int *pfd1, int *pfd2, int *pfd3) {

	int* child1Results = (int*) malloc(sizeof(int) * num_of_boards);
	int* child2Results = (int*) malloc(sizeof(int) * num_of_boards);
	int* child3Results = (int*) malloc(sizeof(int) * num_of_boards);

	char *newargv1[] = { "./CheckSudokuBoard", "-r", NULL };
	char *newargv2[] = { "./CheckSudokuBoard", "-c", NULL };
	char *newargv3[] = { "./CheckSudokuBoard", "-m", NULL };

	create_fork_for_pipe(boards_as_string, num_of_boards, pfd1, newargv1,
			child1Results);
	create_fork_for_pipe(boards_as_string, num_of_boards, pfd2, newargv2,
			child2Results);
	create_fork_for_pipe(boards_as_string, num_of_boards, pfd3, newargv3,
			child3Results);

	int i;
	for (i = 0; i < num_of_boards; i++) {
		int result = 0;
		result += child1Results[i];
		result += child2Results[i];
		result += child3Results[i];
		printf("%s is %s\n", (!argv[i + 1] ? "manual solution" : argv[i + 1]),
				(result == 3 ? "legal" : "not legal"));
	}
	free(child1Results);
	free(child2Results);
	free(child3Results);
	free(boards_as_string);
}

int open_pipes(int* pfd1, int* pfd2, int* pfd3) {
	if ((pipe(pfd1) < 0) || (pipe(pfd2) < 0) || (pipe(pfd3) < 0)) {
		perror("pipe");
		return 0;
	}
	return 1;
}

void get_boards_for_processes(int argc, char* argv[]) {
	int i, pfd1[2], pfd2[2], pfd3[2];
	int num_of_boards = (argc - 1 == 0 ? 1 : argc - 1);
	int** boards = (int**) malloc(sizeof(int*) * num_of_boards);
	char* boards_as_string = (char*) malloc(
			sizeof(char) * num_of_boards * SIZE * SIZE);
	char* board_as_string = (char*) malloc(sizeof(char) * SIZE * SIZE);
	if ((!boards) || (!boards_as_string) || (!board_as_string)) {
		perror("malloc");
		exit(-1);
	}
	sprintf(boards_as_string, "%d", num_of_boards);
	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			boards[i - 1] = read_board_from_file(argv[i]);
		}
		for (i = 0; i < num_of_boards; i++) {
			board_as_string = convert_board_to_string(boards[i]);
			memcpy((boards_as_string + 1 + (i * SIZE * SIZE)), board_as_string,
					sizeof(char) * SIZE * SIZE + 1);
		}
	} else {
		boards[0] = read_board_from_user();
		board_as_string = convert_board_to_string(boards[0]);
		memcpy((boards_as_string + 1), board_as_string,
				sizeof(char) * SIZE * SIZE + 1);
	}
	if (!open_pipes(pfd1, pfd2, pfd3)) {
		perror("pipe");
		exit(-1);
	}
	create_child_processes(argv, boards_as_string, num_of_boards, pfd1, pfd2,
			pfd3);
	free(boards);
	free(boards_as_string);
}

int main(int argc, char* argv[]) {
	get_boards_for_processes(argc, argv);
	return EXIT_SUCCESS;
}
