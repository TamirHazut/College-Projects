/*
 * func.c
 *
 *  Created on: Nov 8, 2018
 *      Author: tamir-ubuntu
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "general_functions.h"

void initMat(int* mat, int rows, int cols, int random) {
	int i;
	for (i = 0; i < rows * cols; i++) {
		*(mat + i) =
				(random == 1 ? getRandom(RANDOM_MIN_VALUE, RANDOM_MAX_VALUE) : i);
	}
}
int getRandom(int min, int max) {
	int val;
	val = rand();
	return min + val % (max - min + 1);
}
void printMat(const int* mat, int rows, int cols) {
	int i, j;
	for (i = 0; i <= rows - 1; i++) {
		for (j = 0; j <= cols - 1; j++) {
			printf("%5d ", *(mat + i * rows + j));
		}
		printf("\n");
	}
}
void swap(int* v1, int* v2) {
	int temp;
	temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

