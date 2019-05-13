#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hw2_b.h"
#include "general.h"
#include "stack.h"

int validArrayForThreadsWithMutex[NUM_OF_TASKS] = { 0 };
int sudoku_board[81];
int condition = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
Stack* tasksStack;

void get_board_for_threads(int argc, char* argv[]) {
	if (argc == 1) {
		int* board_from_user = read_board_from_user();
		memcpy(sudoku_board, board_from_user, sizeof(int) * SIZE * SIZE);
		start_threads_with_mutex("manual solution");
		free(board_from_user);
	} else {
		memcpy(sudoku_board, read_board_from_file(argv[1]),
				sizeof(int) * SIZE * SIZE);
		start_threads_with_mutex(argv[1]);
	}
}

void start_threads_with_mutex(char* filename) {
	pthread_t threads_handlers[NUM_OF_THREADS_WITH_MUTEX];
	int i;
	create_tasks_for_threads();
	for (i = 0; i < NUM_OF_THREADS_WITH_MUTEX; i++) {
		pthread_create(&threads_handlers[i], NULL, get_task_from_list, NULL);
	}
	for (i = 0; i < NUM_OF_THREADS_WITH_MUTEX; i++) {
		pthread_join(threads_handlers[i], NULL);
	}
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
	free(tasksStack);
	checkValidArray(validArrayForThreadsWithMutex, filename);
}

void create_tasks_for_threads() {
	int i, j;
	tasksStack = initStack(sizeof(Task), NUM_OF_TASKS);
	if (!tasksStack) {
		return;
	}
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (i % 3 == 0 && j % 3 == 0) {
				Task* task = (Task*) malloc(sizeof(Task));
				task->row = i;
				task->column = j;
				task->type = MATRIX;
				push(tasksStack, task);
			}
			if (i == 0) {
				Task* task = (Task*) malloc(sizeof(Task));
				task->row = i;
				task->column = j;
				task->type = COLUMN;
				push(tasksStack, task);
			}
			if (j == 0) {
				Task* task = (Task*) malloc(sizeof(Task));
				task->row = i;
				task->column = j;
				task->type = ROW;
				push(tasksStack, task);
			}
		}
	}
}

void* get_task_from_list(void* args) {
	Task task;
	while(!isEmpty(tasksStack)) {
		pthread_mutex_lock(&lock);
		while (condition) {
			pthread_cond_wait(&cond, &lock);
		}
		condition = 1;
		pop(tasksStack, &task);
		condition = 0;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
		doTask(&task);
	}
	pthread_exit(NULL);
}

void doTask(Task* task) {
	switch (task->type) {
	case ROW:
		validArrayForThreadsWithMutex[task->row] = checkForValidRow(
				sudoku_board, task->row);
		break;
	case COLUMN:
		validArrayForThreadsWithMutex[task->column + SIZE] =
				checkForValidColumn(sudoku_board, task->column);
		break;
	case MATRIX:
		validArrayForThreadsWithMutex[task->row + task->column / 3 + SIZE * 2] =
				checkForValidMatrix(sudoku_board, task->row, task->column);
		break;
	}
}

int main(int argc, char* argv[]) {
	get_board_for_threads(argc, argv);
	return EXIT_SUCCESS;
}
