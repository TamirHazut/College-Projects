/*
 * exe.c
 *
 *  Created on: Nov 8, 2018
 *      Author: tamir-ubuntu
 */

#include <ctype.h>
#include <stdio.h>
#include "main_menu.h"
#include "general_functions.h"
#include "picture_manipulation.h"
#include "number_game.h"

void startMainMenu() {
	boolean leave;
	leave = FALSE;
	int size;
	size = getRandom(MIN_MAT_SIZE, MAX_MAT_SIZE);
	int mat[size][size];
	while (!leave) {
		showMainMenuMessage();
		char choice;
		scanf("%c", &choice);
		getchar();
		checkMainChoice(choice, &leave, (int*) mat, size);
	}

}

void checkMainChoice(char choice, boolean* leave, int* mat, int size) {
	switch (tolower(choice)) {
	case 'p':
		startPictureManipulating(mat, size);
		break;
	case 'n':
		startNumberGame(mat, size);
		break;
	case 'e':
		quitMainMenu(leave);
		break;
	}
}

void quitMainMenu(boolean* leave) {
	printf("Bye Bye.\n");
	*leave = TRUE;
}

void showMainMenuMessage() {
	printf("Please choose one of the following options:\n");
	printf("\nP/p - Picture Manipulation");
	printf("\nN/n - Number Game");
	printf("\nE/e - Quit\n");
}
