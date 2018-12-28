/*
 * HW3_TamirHazut.c
 *
 *  Created on: Dec 12, 2018
 *      Author: tamir-ubuntu
 */
#include <stdio.h>
#include "general_functions.h"
#include "city.h"

int main() {
	City utz = { NULL, 0 };
	int uReq;

	//first time read
	readCity(&utz);
	do {
		uReq = menu();
		switch (uReq) {
		case READ_CITY:
			readCity(&utz);
			break;

		case SHOW_CITY:
			showCityGardens(&utz);
			break;

		case SHOW_GARDEN:
			showSpecificGardenInCity(&utz);
			break;

		case WRITE_CITY:
			saveCity(&utz);
			break;

		case ADD_GARDEN:
			cityAddGarden(&utz);
			break;

		case ADD_CHILD:
			addChildToSpecificGardenInCity(&utz);
			break;

		case CHILD_BIRTHDAY:
			birthdayToChild(&utz);
			break;

		case COUNT_GRADUATE:
			printf("There are %d children going to school next year\n",
					countChova(&utz));
			break;

		}
	} while (uReq != EXIT);

	ReleaseCity(&utz); //free all allocations

	return 1;
}
