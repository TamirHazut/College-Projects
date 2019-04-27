/*
 * checksudokurows.h
 *
 *  Created on: Apr 10, 2019
 *      Author: tamir-ubuntu
 */

#ifndef CHECKSUDOKUROWS_H_
#define CHECKSUDOKUROWS_H_

#define SIZE 9

int checkForValidRows(const int* sudoku_board);
int checkForValidRow(const int* sudoku_row, int row);
void fillArray(int* arr, int length);
int* get_board_from_string(char temp[SIZE * SIZE]);

#endif /* CHECKSUDOKUROWS_H_ */
