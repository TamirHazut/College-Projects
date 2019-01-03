#include <stdio.h>

#include "City.h"
#include "Kindergarten.h"

void readCity(City* pCity) {
	if (pCity->pGardenList != NULL) {
		releaseCity(pCity);
		pCity->count = 0;
	}
	pCity->pGardenList = readAllGardensFromFile(DATA_FILE, &pCity->count);

	if (pCity->pGardenList == NULL)
		printf("Error reading city information\n");
}

void showCityGardens(City* pCity) {
	showAllGardens(pCity->pGardenList, pCity->count);
}

void showSpecificGardenInCity(City* pCity) {
	showGardenMenu(pCity->pGardenList, pCity->count);
}

void saveCity(City* pCity) {
	writeGardensToFile(pCity->pGardenList, pCity->count, DATA_FILE);
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
	genericInsertionSort(pCity->pGardenList, pCity->count, sizeof(Garden*),
			compareByKindergartenName);
}
void sortByTypeAndNumOfChildren(City* pCity) {
	genericInsertionSort(pCity->pGardenList, pCity->count, sizeof(Garden*),
			compareByKindergartenTypeAndNumOfChildren);
}
void sortByChildrenID(City* pCity) {
	SortKindergartenByChildrenID(pCity->pGardenList, pCity->count);
}

void releaseCity(City* pCity) {
	release(pCity->pGardenList, pCity->count);
}

