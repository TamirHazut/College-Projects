/*
 * number_game.h
 *
 *  Created on: Nov 11, 2018
 *      Author: tamir-ubuntu
 */

#ifndef NUMBER_GAME_H_
#define NUMBER_GAME_H_

void startNumberGame(int* mat, int size);
void shuffleMat(int* mat, int rows, int cols);
void checkMoves(int* mat, int rows, int cols);
int checkBoardForFinish(int* mat, int rows, int cols);
int getPlayersChoice();
void checkValidChoice(int* mat, int rows, int cols, int playerChoice,
		int* currentEmptyRowIndex, int* currentEmptyColIndex);
int checkLeftSide(int* currentEmptyColIndex, int* emptySlot, int playerChoice);
int checkRightSide(int cols, int* currentEmptyColIndex, int* emptySlot,
		int playerChoice);
int checkUpperSide(int rows, int* currentEmptyRowIndex, int* emptySlot,
		int playerChoice);
int checkLowerSide(int rows, int* currentEmptyRowIndex, int* emptySlot,
		int playerChoice);
void findCurrentEmptyIndex(const int* mat, int rows, int cols,
		int* currentEmptyRowIndex, int* currentEmptyColIndex);
#endif /* NUMBER_GAME_H_ */
