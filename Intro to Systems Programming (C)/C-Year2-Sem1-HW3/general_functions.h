/*
 * general_functions.h
 *
 *  Created on: Dec 12, 2018
 *      Author: tamir-ubuntu
 */

#ifndef GENERAL_FUNCTIONS_H_
#define GENERAL_FUNCTIONS_H_
#include <stdlib.h>

enum MenuOptions {
	EXIT,
	READ_CITY,
	SHOW_CITY,
	SHOW_GARDEN,
	WRITE_CITY,
	ADD_GARDEN,
	ADD_CHILD,
	CHILD_BIRTHDAY,
	COUNT_GRADUATE,
};

int menu();
void printMenu();

#endif /* GENERAL_FUNCTIONS_H_ */
