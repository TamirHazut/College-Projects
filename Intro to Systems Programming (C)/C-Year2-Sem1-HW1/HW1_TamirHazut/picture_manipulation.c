/*
 * picture_manipulation.c
 *
 *  Created on: Nov 11, 2018
 *      Author: tamir-ubuntu
 */
#include <stdio.h>
#include "picture_manipulation.h"

void startPictureManipulating(int* mat, int size) {
	initMat(mat, size, size, 1);
	printMat(mat, size, size);
	pictureManipulationMenu(mat, size);
}
void pictureManipulationMenu(int* mat, int size) {
	boolean leavePictureManipulationMenu;
	leavePictureManipulationMenu = FALSE;
	while (!leavePictureManipulationMenu) {
		showPictureManipulationMenuMessage();
		int choicePictureManipulation;
		scanf("%d", &choicePictureManipulation);
		getchar();
		checkPictureManipulationChoice(mat, size, size,
				choicePictureManipulation, &leavePictureManipulationMenu);
	}
}
void showPictureManipulationMenuMessage() {
	printf("\nPlease choose one of the following options:\n");
	printf("\n1 - 90 degree clockwise");
	printf("\n2 - 90 degree counter clockwise");
	printf("\n3 - Flip Horizontal");
	printf("\n4 - Flip Vertical");
	printf("\n-1 - Quit\n");
}

void checkPictureManipulationChoice(int* mat, int rows, int cols, int choice,
		boolean* leave) {
	switch (choice) {
	case 1:
		printf("\n--------- Picture after manipulation ---------\n");
		change90Degree(mat, rows, cols, 1);
		printMat(mat, rows, cols);
		break;
	case 2:
		printf("\n--------- Picture after manipulation ---------\n");
		change90Degree(mat, rows, cols, 0);
		printMat(mat, rows, cols);
		break;
	case 3:
		printf("\n--------- Picture after manipulation ---------\n");
		flipHorizontal(mat, rows, cols);
		printMat(mat, rows, cols);
		break;
	case 4:
		printf("\n--------- Picture after manipulation ---------\n");
		flipVertical(mat, rows, cols);
		printMat(mat, rows, cols);
		break;
	case -1:
		*leave = TRUE;
		break;
	}
}
void transpose(int* mat, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = i; j < cols; j++) {
			swap(&(*(mat + i * rows + j)), &(*(mat + j * cols + i)));
		}
	}
}
void flipVertical(int* mat, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols / 2; j++) {
			swap(&(*(mat + i * rows + j)), &(*(mat + i * rows + cols - 1 - j)));
		}
	}
}
void flipHorizontal(int* mat, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows / 2; i++) {
		for (j = 0; j < cols; j++) {
			swap(&(*(mat + i * rows + j)),
					&(*(mat + (rows - 1 - i) * rows + j)));
		}
	}
}
void change90Degree(int* mat, int rows, int cols, int clockwise) {
	if (clockwise == 0) {
		transpose(mat, rows, cols);
		flipHorizontal(mat, rows, cols);
	} else if (clockwise == 1) {
		flipHorizontal(mat, rows, cols);
		transpose(mat, rows, cols);

	}
}

