#ifndef __CITY__
#define __CITY__

#include "Kindergarten.h"
#include "List.h"

#define DATA_TXT_FILE "DataFile.txt"
#define DATA_BIN_FILE "DataFile.bin"

typedef struct {
	Garden** pGardenList;
	int count;
} City;

void readCity(City* pCity, int typeOfFile);
void showCityGardens(City* pCity);
void showSpecificGardenInCity(City* pCity);
void saveCity(City* pCity, int typeOfFile);
void cityAddGarden(City* pCity);
void addChildToSpecificGardenInCity(City* pCity);
void birthdayToChild(City* pCity);
int countChova(City* pCity);
void sortByKindergartenName(City* pCity);
void sortByTypeAndNumOfChildren(City* pCity);
void sortByChildrenID(City* pCity);
void kindergartensLinkedList(City* pCity);
LIST* createLinkedListForKindergartenType(City* pCity,
		int typeToCreateLinkedList);
void displayKindergartensFromList(LIST* list);
void releaseCity(City* pCity);

#endif
