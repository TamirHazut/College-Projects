/*
 * checksudokurows.h
 *
 *  Created on: Apr 10, 2019
 *      Author: tamir-ubuntu
 */

#ifndef CHECKSUDOKUMATRICES_H_
#define CHECKSUDOKUMATRICES_H_

#define SIZE 9

int checkForValidMatrices(const int* soduku_board);
int checkForValidMatrix(const int* sudoku_board, int row, int col);
void fillArray(int* arr, int length);
int* get_board_from_string(char temp[SIZE * SIZE]);

#endif /* CHECKSUDOKUMATRICES_H_ */
