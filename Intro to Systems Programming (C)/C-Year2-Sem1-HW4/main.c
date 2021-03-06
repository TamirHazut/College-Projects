#include <stdio.h>
#include <stdlib.h>

#include "General.h"
#include "Kindergarten.h"
#include "Child.h"
#include "City.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		return 0;
	}
	int typeOfFile;
	sscanf(argv[1],"%d",&typeOfFile);
	printf("%d",typeOfFile);
	City utz = { NULL, 0 };
	int uReq;

	//first time read
	readCity(&utz,typeOfFile);
	do {
		uReq = menu();
		switch (uReq) {
		case READ_CITY:
			readCity(&utz,typeOfFile);
			break;

		case SHOW_CITY:
			showCityGardens(&utz);
			break;

		case SHOW_GARDEN:
			showSpecificGardenInCity(&utz);
			break;

		case WRITE_CITY:
			saveCity(&utz,typeOfFile);
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
		case SORT_BY_NAME:
			sortByKindergartenName(&utz);
			break;
		case SORT_BY_NUM_OF_CHILDREN:
			sortByTypeAndNumOfChildren(&utz);
			break;
		case SORT_BY_CHILDREN_ID:
			sortByChildrenID(&utz);
			break;
		case LINKED_LIST:
			kindergartensLinkedList(&utz);
			break;
		}

	} while (uReq != EXIT);

	releaseCity(&utz); //free all allocations

	return EXIT_SUCCESS;
}

