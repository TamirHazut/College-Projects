/*
 * func.h
 *
 *  Created on: Nov 8, 2018
 *      Author: tamir-ubuntu
 */

#ifndef FUNC_H_
#define FUNC_H_

typedef enum { FALSE, TRUE } boolean;

#define MAX_MAT_SIZE 6
#define MIN_MAT_SIZE 4
#define RANDOM_MIN_VALUE 1
#define RANDOM_MAX_VALUE 100

void initMat(int* mat, int rows, int cols, int random);
void printMat(const int* mat, int rows, int cols);
int getRandom(int min, int max);
void swap(int* v1, int* v2);

#endif /* FUNC_H_ */
