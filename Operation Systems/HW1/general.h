#ifndef GENERAL_H_
#define GENERAL_H_
#define SIZE 9
#define DEFAULT_VAULE 1

int* read_board_from_file(char* filename);
int* read_board_from_user();
int checkForValidRows(int* soduku_board);
int checkForValidRow(int* sudoku_board, int row);
int checkForValidColumns(int* soduku_board);
int checkForValidColumn(int* sudoku_board, int col);
int checkForValidMatrices(int* soduku_board);
int checkForValidMatrix(int* sudoku_board, int row, int col);
char* convert_board_to_string(int *board);
int* convert_board_from_string(char temp[SIZE * SIZE]);

#endif /* GENERAL_H_ */
