#ifndef HW2_B_H_
#define HW2_B_H_

#define NUM_OF_THREADS_WITH_MUTEX 3
#define SIZE 9

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

#endif /* HW2_B_H_ */

