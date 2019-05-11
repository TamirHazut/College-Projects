#ifndef V1_H_
#define V1_H_

#define NUM_OF_PROCESSES 3

void create_child_processes(char* argv[], char* boards_as_string,
		int num_of_boards, int *pfd1, int *pfd2, int *pfd3);
void change_pipe_fd_channel(int *pfd);
void create_fork_for_pipe(char* boards_as_string, int num_of_boards, int *pfd,
		char* newargv[], int* childResults);
void check_solution_using_pipe(int num_of_boards, int *pfd, int* childResults);
int open_pipes(int* pfd1, int* pfd2, int* pfd3);
void get_board_for_processes(int argc, char* argv[]);

#endif /* V1_H_ */
