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
int tasksCondition = 0, parentCondition = NUM_OF_THREADS_WITH_MUTEX-1;
pthread_mutex_t tasksLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t tasksCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t parentLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t parentCond = PTHREAD_COND_INITIALIZER;
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
	pthread_mutex_lock(&parentLock);
	while (parentCondition > 0) {
		pthread_cond_wait(&parentCond, &parentLock);
	}
	for (i = 0; i < NUM_OF_THREADS_WITH_MUTEX; i++) {
		pthread_join(threads_handlers[i], NULL);
	}
	pthread_mutex_destroy(&tasksLock);
	pthread_cond_destroy(&tasksCond);
	pthread_mutex_destroy(&parentLock);
	pthread_cond_destroy(&parentCond);
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
	pthread_mutex_lock(&parentLock);
	while (!isEmpty(tasksStack)) {
		pthread_mutex_lock(&tasksLock);
		while (tasksCondition) {
			pthread_cond_wait(&tasksCond, &tasksLock);
		}
		tasksCondition = 1;
		pop(tasksStack, &task);
		tasksCondition = 0;
		pthread_cond_signal(&tasksCond);
		pthread_mutex_unlock(&tasksLock);
		if (!doTask(&task)) {
			clearStack(tasksStack);
			break;
		}
	}
	if (parentCondition == 0) {
		pthread_cond_signal(&parentCond);
	}
	parentCondition--;
	pthread_mutex_unlock(&parentLock);
	pthread_exit(NULL);
}

int doTask(Task* task) {
	int taskResult = 0;
	switch (task->type) {
	case ROW:
		taskResult = checkForValidRow(sudoku_board, task->row);
		validArrayForThreadsWithMutex[task->row] = taskResult;
		break;
	case COLUMN:
		taskResult = checkForValidColumn(sudoku_board, task->column);
		validArrayForThreadsWithMutex[task->column + SIZE] = taskResult;
		break;
	case MATRIX:
		taskResult = checkForValidMatrix(sudoku_board, task->row, task->column);
		validArrayForThreadsWithMutex[task->row + task->column / 3 + SIZE * 2] =
				taskResult;
		break;
	}
	return taskResult;
}

int main(int argc, char* argv[]) {
	get_board_for_threads(argc, argv);
	return EXIT_SUCCESS;
}
