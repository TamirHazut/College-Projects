/*
 * exe.h
 *
 *  Created on: Nov 8, 2018
 *      Author: tamir-ubuntu
 */

#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include "general_functions.h"

void startMainMenu();
void checkMainChoice(char choice, boolean* leave, int* mat, int size);
void showMainMenuMessage();
void quitMainMenu(boolean* leave);

#endif /* MAIN_MENU_H_ */
