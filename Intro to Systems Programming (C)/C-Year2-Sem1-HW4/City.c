#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "City.h"
#include "General.h"
#include "Kindergarten.h"
#include "List.h"

void readCity(City* pCity, int typeOfFile) {
	if (pCity->pGardenList != NULL) {
		releaseCity(pCity);
		pCity->count = 0;
	}
	if (typeOfFile) {
		pCity->pGardenList = readAllGardensFromBinFile(DATA_BIN_FILE,
				&pCity->count);
	} else {
		pCity->pGardenList = readAllGardensFromTextFile(DATA_TXT_FILE,
				&pCity->count);
	}
	if (pCity->pGardenList == NULL)
		printf("Error reading city information\n");
}

void showCityGardens(City* pCity) {
	showAllGardens(pCity->pGardenList, pCity->count);
}

void showSpecificGardenInCity(City* pCity) {
	showGardenMenu(pCity->pGardenList, pCity->count);
}

void saveCity(City* pCity, int typeOfFile) {
	if (typeOfFile) {
		writeGardensToBinFile(pCity->pGardenList, pCity->count, DATA_BIN_FILE);
	} else {
		writeGardensToTextFile(pCity->pGardenList, pCity->count, DATA_TXT_FILE);
	}
}

void cityAddGarden(City* pCity) {
	pCity->pGardenList = addGarden(pCity->pGardenList, &pCity->count);
	if (pCity->pGardenList == NULL) //Allocation error
		printf("Error adding kindergarten\n");
}

void addChildToSpecificGardenInCity(City* pCity) {
	addChildToGarden(pCity->pGardenList, pCity->count);
}

void birthdayToChild(City* pCity) {
	handleBirthdayToChild(pCity->pGardenList, pCity->count);
}

int countChova(City* pCity) {
	int i;
	int count = 0;
	for (i = 0; i < pCity->count; i++) {
		if (pCity->pGardenList[i]->type == Chova)
			count += pCity->pGardenList[i]->childCount;
	}
	return count;
}

void sortByKindergartenName(City* pCity) {
	insertionSort(pCity->pGardenList, pCity->count, sizeof(Garden*),
			compareByKindergartenName);
}
void sortByTypeAndNumOfChildren(City* pCity) {
	insertionSort(pCity->pGardenList, pCity->count, sizeof(Garden*),
			compareByKindergartenTypeAndNumOfChildren);
}
void sortByChildrenID(City* pCity) {
	SortKindergartenByChildrenID(pCity->pGardenList, pCity->count);
}

void kindergartensLinkedList(City* pCity) {
	int typeToCreateLinkedList;
	LIST* list;
	typeToCreateLinkedList = getTypeOption();
	list = createLinkedListForKindergartenType(pCity, typeToCreateLinkedList);
	if (list != NULL) {
		displayKindergartensFromList(list);
		free(list);
	}
}
LIST* createLinkedListForKindergartenType(City* pCity,
		int typeToCreateLinkedList) {
	LIST tempList;
	LIST* list;
	NODE* pNode;
	int i;
	L_init(&tempList);
	pNode = &tempList.head;
	for (i = 0; i < pCity->count; i++) {
		if (pCity->pGardenList[i]->type == typeToCreateLinkedList) {
			pNode = L_insert(pNode, pCity->pGardenList[i]);
		}
	}
	list = (LIST*) malloc(sizeof(tempList));
	if (!checkAllocation(list)) {
		return NULL;
	}
	memcpy(list, &tempList, sizeof(tempList));
	return list;
}
void displayKindergartensFromList(LIST* list) {
	printf("Kindergartens list:\n");
	L_print(list, showGarden);
}

void releaseCity(City* pCity) {
	release(pCity->pGardenList, pCity->count);
}

