#ifndef GENERAL_H_
#define GENERAL_H_
#define SIZE 9
#define DEFAULT_VAULE 1
#define NUM_OF_TASKS 27

int* read_board_from_file(char* filename);
int* read_board_from_user();
int checkForValidRow(int* sudoku_board, int row);
int checkForValidColumn(int* sudoku_board, int col);
int checkForValidMatrix(int* sudoku_board, int row, int col);
void checkValidArray(int* validArray, char* filename);

#endif /* GENERAL_H_ */
