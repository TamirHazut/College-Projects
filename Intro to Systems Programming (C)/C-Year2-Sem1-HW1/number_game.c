/*
 * number_game.c
 *
 *  Created on: Nov 11, 2018
 *      Author: tamir-ubuntu
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "number_game.h"
#include "general_functions.h"

#define MIN_RANDOM_VALUE_FOR_SHUFFLE 0
#define MAX_RANDOM_VALUE_FOR_SHUFFLE 30

void startNumberGame(int* mat, int size) {
	initMat(mat, size, size, 0);
	shuffleMat(mat, size, size);
	printMat(mat, size, size);
	checkMoves(mat, size, size);
}
void shuffleMat(int* mat, int rows, int cols) {
	int i, maxTimesToShuffle, randomIndex1, randomIndex2;
	maxTimesToShuffle = getRandom(MIN_RANDOM_VALUE_FOR_SHUFFLE,
	MAX_RANDOM_VALUE_FOR_SHUFFLE);
	for (i = 0; i < maxTimesToShuffle; i++) {
		randomIndex1 = getRandom(0, rows * cols - 1);
		randomIndex2 = getRandom(0, rows * cols - 1);
		swap(&(*(mat + randomIndex1)), &(*(mat + randomIndex2)));
	}
}
void findCurrentEmptyIndex(const int* mat, int rows, int cols,
		int* currentEmptyRowIndex, int* currentEmptyColIndex) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if (*(mat + (i * rows) + j) == 0) {
				*currentEmptyRowIndex = i;
				*currentEmptyColIndex = j;
			}
		}
	}
}
void checkMoves(int* mat, int rows, int cols) {
	boolean finishNumberGame;
	int currentEmptyRowIndex, currentEmptyColIndex;
	findCurrentEmptyIndex(mat, rows, cols, &currentEmptyRowIndex,
			&currentEmptyColIndex);
	finishNumberGame = checkBoardForFinish(mat, rows, cols);
	while (finishNumberGame == FALSE) {
		finishNumberGame = checkBoardForFinish(mat, rows, cols);
		int playerChoice;
		playerChoice = getPlayersChoice();
		if (playerChoice == -1) {
			finishNumberGame = TRUE;
		} else {
			checkValidChoice(mat, rows, cols, playerChoice,
					&currentEmptyRowIndex, &currentEmptyColIndex);
			finishNumberGame = checkBoardForFinish(mat, rows, cols);
		}
	}
}
int checkBoardForFinish(int* mat, int rows, int cols) {
	int i;
	if (*(mat + rows * cols - 1) != 0) {
		return FALSE;
	}
	for (i = 0; i < rows * cols - 1; i++) {
		if (*(mat + i) != i + 1) {
			return FALSE;
		}
	}
	printf("\nYow win! The game is over!\n");
	return TRUE;
}
int getPlayersChoice() {
	int playersChoice;
	printf("Your step ('-1' to quit):");
	scanf("%d", &playersChoice);
	getchar();
	return playersChoice;
}
int checkLeftSide(int* currentEmptyColIndex, int* emptySlot, int playerChoice) {
	if ((*currentEmptyColIndex != 0) && (*(emptySlot - 1) == playerChoice)) {
		swap(&(*(emptySlot - 1)), emptySlot);
		*currentEmptyColIndex = *currentEmptyColIndex - 1;
		return 1;
	}
	return 0;
}
int checkRightSide(int cols, int* currentEmptyColIndex, int* emptySlot,
		int playerChoice) {
	if ((*currentEmptyColIndex != cols - 1)
			&& (*(emptySlot + 1) == playerChoice)) {
		swap(&(*(emptySlot + 1)), emptySlot);
		*currentEmptyColIndex = *currentEmptyColIndex + 1;
		return 1;
	}
	return 0;
}
int checkUpperSide(int rows, int* currentEmptyRowIndex, int* emptySlot,
		int playerChoice) {
	if ((*currentEmptyRowIndex != 0) && (*(emptySlot - rows) == playerChoice)) {
		swap(&(*(emptySlot - rows)), emptySlot);
		*currentEmptyRowIndex = *currentEmptyRowIndex - 1;
		return 1;
	}
	return 0;
}
int checkLowerSide(int rows, int* currentEmptyRowIndex, int* emptySlot,
		int playerChoice) {
	if ((*currentEmptyRowIndex != rows - 1)
			&& (*(emptySlot + rows) == playerChoice)) {
		swap(&(*(emptySlot + rows)), emptySlot);
		*currentEmptyRowIndex = *currentEmptyRowIndex + 1;
		return 1;
	}
	return 0;
}
void checkValidChoice(int* mat, int rows, int cols, int playerChoice,
		int* currentEmptyRowIndex, int* currentEmptyColIndex) {
	int movedLeft, movedRight, movedUp, movedDown, *emptySlot;
	emptySlot = &(*(mat + (*currentEmptyRowIndex) * rows
			+ (*currentEmptyColIndex)));
	movedLeft = checkLeftSide(currentEmptyColIndex, emptySlot, playerChoice);
	movedRight = checkRightSide(cols, currentEmptyColIndex, emptySlot,
			playerChoice);
	movedUp = checkUpperSide(rows, currentEmptyRowIndex, emptySlot,
			playerChoice);
	movedDown = checkLowerSide(rows, currentEmptyRowIndex, emptySlot,
			playerChoice);
	if ((movedLeft) || (movedRight) || (movedUp) || (movedDown)) {
		printMat(mat, rows, cols);
	} else {
		printf("Invalid step!\n");
	}
}
