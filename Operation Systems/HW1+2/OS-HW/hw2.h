#ifndef HW2_H_
#define HW2_H_

#define NUM_OF_THREADS_WITHOUT_MUTEX 27
#define NUM_OF_TASKS 27
#define NUM_OF_THREADS_WITH_MUTEX 10

typedef struct {
	int row;
	int column;
} Indexes;

typedef enum {
	ROW, COLUMN, MATRIX
} Checks;

typedef struct {
	int row;
	int column;
	int type;
} Task;

void get_board_for_threads(int argc, char* argv[]);

void start_threads_with_mutex(char* filename);
void create_tasks_for_threads();
void* get_task_from_list(void* args);
void doTask(Task* task);

void start_threads_without_mutex(char* filename);
void *isValidRow(void* args);
void *isValidColumn(void* args);
void *isValidMatrix(void* args);
void checkValidArray(char* filename);

#endif /* HW2_H_ */

