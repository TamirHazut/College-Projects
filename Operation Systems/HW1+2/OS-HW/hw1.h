#ifndef HW1_H_
#define HW1_H_

#include "general.h"

typedef struct {
	int solution[81];
	int status[3];
} Shared_Struct_For_Processes;

void get_board_for_processes(int argc, char* argv[]);
void split_work_using_mmap(Shared_Struct_For_Processes* sudoku, char* filename);
void check_solution_using_mmap(Shared_Struct_For_Processes* shared_sudoku, char* filename);
char* create_writing_channel(int pfd[]);
void create_fork_for_pipe(int pfd[], char* newargv[], char* newenviron[]);
void check_solution_using_pipe(int* board, char* filename);

#endif /* HW1_H_ */
