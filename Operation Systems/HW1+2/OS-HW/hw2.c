#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hw2.h"
#include "general.h"
#include "stack.h"

int validArrayForThreadsWithoutMutex[NUM_OF_THREADS_WITHOUT_MUTEX] = { 0 };
int sudoku_board[81];

int validArrayForThreadsWithMutex[NUM_OF_THREADS_WITHOUT_MUTEX] = { 0 };
pthread_mutex_t lock;
pthread_cond_t cond;
Stack* tasksStack;

void get_board_for_threads(int argc, char* argv[]) {
	if (argc == 1) {
		int* board_from_user = read_board_from_user();
		memcpy(sudoku_board, board_from_user, sizeof(int) * SIZE * SIZE);
		start_threads_without_mutex("STDIN");
		start_threads_with_mutex("STDIN");
		free(board_from_user);
	} else {
		read_board_from_file(argv[1], sudoku_board);
		start_threads_without_mutex(argv[1]);
		start_threads_with_mutex(argv[1]);
	}
}

void start_threads_with_mutex(char* filename) {
	pthread_t threads_handlers[NUM_OF_THREADS_WITH_MUTEX];
	int i;
	if (pthread_mutex_init(&lock, NULL) != 0
			|| pthread_cond_init(&cond, NULL) != 0) {
		printf("Mutex/Condition init has failed.\n");
		return;
	}
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
	checkValidArray(filename);
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
	for (;;) {
		pthread_mutex_lock(&lock);
		if (isEmpty(tasksStack)) {
			pthread_mutex_unlock(&lock);
			pthread_exit(NULL);
		}
		pop(tasksStack, &task);
		pthread_mutex_unlock(&lock);
		doTask(&task);
	}
	pthread_exit(NULL);
}

void doTask(Task* task) {
	switch (task->type) {
	case ROW:
		validArrayForThreadsWithMutex[task->row] = checkForValidRow(sudoku_board, task->row);
		break;
	case COLUMN:
		validArrayForThreadsWithMutex[task->column + SIZE] = checkForValidColumn(sudoku_board, task->column);
		break;
	case MATRIX:
		validArrayForThreadsWithMutex[task->row + task->column/3 + SIZE*2] = checkForValidMatrix(sudoku_board, task->row, task->column);
		break;
	}
}

void start_threads_without_mutex(char* filename) {
	pthread_t threads_handlers[NUM_OF_THREADS_WITHOUT_MUTEX];
	int i, j, threadIndex = 0;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (i % 3 == 0 && j % 3 == 0) {
				Indexes* matrixIndexes = (Indexes*) malloc(sizeof(Indexes));
				matrixIndexes->row = i;
				matrixIndexes->column = j;
				pthread_create(&threads_handlers[threadIndex++], NULL,
						isValidMatrix, (void*) matrixIndexes);
			}
			if (i == 0) {
				Indexes* columnIndexes = (Indexes*) malloc(sizeof(Indexes));
				columnIndexes->row = i;
				columnIndexes->column = j;
				pthread_create(&threads_handlers[threadIndex++], NULL,
						isValidColumn, (void*) columnIndexes);

			}
			if (j == 0) {
				Indexes* rowIndexes = (Indexes*) malloc(sizeof(Indexes));
				rowIndexes->row = i;
				rowIndexes->column = j;
				pthread_create(&threads_handlers[threadIndex++], NULL,
						isValidRow, (void*) rowIndexes);
			}
		}
	}
	for (i = 0; i < NUM_OF_THREADS_WITHOUT_MUTEX; i++) {
		pthread_join(threads_handlers[i], NULL);
	}
	checkValidArray(filename);
}

void *isValidRow(void* args) {
	Indexes* params = (Indexes*) args;
	int row = params->row;
	if (params->column != 0 || row >= SIZE) {
		pthread_exit(NULL);
	}
	int i;
	for (i = 0; i < SIZE; i++) {
		validArrayForThreadsWithoutMutex[i] = checkForValidRow(sudoku_board, row);
	}
	pthread_exit(NULL);
}

void *isValidColumn(void* args) {
	Indexes* params = (Indexes*) args;
	int column = params->column;
	if (params->row != 0 || column >= SIZE) {
		pthread_exit(NULL);
	}
	int i;
	for (i = 0; i < SIZE; i++) {
		validArrayForThreadsWithoutMutex[i + SIZE] = checkForValidColumn(sudoku_board,
				column);
	}
	pthread_exit(NULL);
}

void *isValidMatrix(void* args) {
	Indexes* params = (Indexes*) args;
	int row = params->row;
	int column = params->column;
	if (column % 3 != 0 || column > 6 || row % 3 != 0 || row > 6) {
		pthread_exit(NULL);
	}
	int i;
	for (i = 0; i < SIZE; i++) {
		validArrayForThreadsWithoutMutex[i + SIZE * 2] = checkForValidMatrix(sudoku_board,
				row, column);
	}
	pthread_exit(NULL);
}

void checkValidArray(char* filename) {
	int i;
	for (i = 0; i < NUM_OF_THREADS_WITHOUT_MUTEX; i++) {
		if (validArrayForThreadsWithoutMutex[i] == 0) {
			printf("%s is Illegal.\n", filename);
			return;
		}
	}
	printf("%s is Legal.\n", filename);
}

