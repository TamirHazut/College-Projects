/*
 * v2.h
 *
 *  Created on: May 10, 2019
 *      Author: tamir-ubuntu
 */

#ifndef V2_H_
#define V2_H_

#define NUM_OF_PROCESSES 3

typedef enum {
	ROWS, COLUMNS, MATRICES
} Checks;

typedef struct {
	int solution[81];
	int status[3];
} Shared_Struct_For_Processes;

Shared_Struct_For_Processes** open_mmap(int num_of_boards);
void close_mmap(Shared_Struct_For_Processes** shared_sudokus, int num_of_boards);

void create_child_processes(char *argv[], Shared_Struct_For_Processes** sudokus,
		int num_of_boards);

void check_solution(Shared_Struct_For_Processes* shared_sudoku, int whatToCheck);

void create_fork_for_mmap(Shared_Struct_For_Processes** shared_sudoku,
		int num_of_boards, int whatToCheck);
#endif /* V2_H_ */
