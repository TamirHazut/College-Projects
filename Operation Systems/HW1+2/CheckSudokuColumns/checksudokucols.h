/*
 * checksudokurows.h
 *
 *  Created on: Apr 10, 2019
 *      Author: tamir-ubuntu
 */

#ifndef CHECKSUDOKUCOLS_H_
#define CHECKSUDOKUCOLS_H_

#define SIZE 9

int checkForValidColumns(const int* sudoku_board);
int checkForValidColumn(const int* sudoku_row, int row);
void fillArray(int* arr, int length);
int* get_board_from_string(char temp[SIZE * SIZE]);

#endif /* CHECKSUDOKUCOLS_H_ */
