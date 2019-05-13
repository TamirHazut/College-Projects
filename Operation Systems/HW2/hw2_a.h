#ifndef HW2_A_H_
#define HW2_A_H_

#define NUM_OF_THREADS_WITHOUT_MUTEX 27
#define SIZE 9

typedef struct {
	int row;
	int column;
} Indexes;

void get_board_for_threads(int argc, char* argv[]);
void start_threads_without_mutex(char* filename);

void *isValidRow(void* args);
void *isValidColumn(void* args);
void *isValidMatrix(void* args);

#endif /* HW2_A_H_ */

