#ifndef GENERAL_H_
#define GENERAL_H_
#define SIZE 9
#define DEFAULT_VAULE 1

void read_board_from_file(char* filename, int* board);
int* read_board_from_user();
int checkForValidRows(int* soduku_board);
int checkForValidRow(int* sudoku_board, int row);
int checkForValidColumns(int* soduku_board);
int checkForValidColumn(int* sudoku_board, int col);
int checkForValidMatrices(int* soduku_board);
int checkForValidMatrix(int* sudoku_board, int row, int col);
void fillArray(int* arr, int length);

#endif /* GENERAL_H_ */
