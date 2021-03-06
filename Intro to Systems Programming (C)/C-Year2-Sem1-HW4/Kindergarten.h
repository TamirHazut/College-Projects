#ifndef __KINDERGARTEN__
#define __KINDERGARTEN__

#define NUM_OF_TOP_TO_DISPLAY 3

#include "Child.h"

typedef enum {
	Chova, TromChova, TromTromChova, NofTypes
} GardenType;

const char* GardenTypeName[NofTypes];

typedef struct {
	char* name;
	GardenType type;
	Child** childPtrArr;
	int childCount;
} Garden;

Garden** readAllGardensFromTextFile(char* fileName, int* pGardenCount);
Garden** readAllGardensFromBinFile(char* fileName, int* pGardenCount);
void readGardenFromTextFile(FILE* fp, Garden* pGarden);
void readGardenFromBinFile(FILE* fp, Garden* pGarden);
GardenType getTypeOption();

void showAllGardens(Garden** pGardenList, int count);
void showTopKindergartens(char* kindergartenName, ...);
void showGarden(const void* pGardenAsVoid);

void writeGardensToTextFile(Garden** pGardenList, int gardenCount, char* fileName);
void writeGardensToBinFile(Garden** pGardenList, int gardenCount, char* fileName);
void writeGardenToTextFile(FILE* fp, const Garden* pGarden);
void writeGardenToBinFile(FILE* fp, const Garden* pGarden);

void addChildToGarden(Garden** pGardenList, int gardenCount);
Garden** addGarden(Garden** pGardenList, int* pGardenCount);

void showGardenMenu(Garden** pGardenList, int count);
Garden* getGardenAskForName(Garden** pGardenList, int count);

Garden* findGardenByName(Garden** pGardenList, int count, const char* name);

Child* getChildAskForId(Garden* pGarden);

void getGardenFromUser(Garden* pGarden, Garden** pGardenList, int count);
void getChildCheckIdFromUser(Child* pChild, const Garden* pGarden);

void handleBirthdayToChild(Garden** pGardenList, int count);

void release(Garden** pGardenList, int count);

int compareByKindergartenName(const void* kidnergarten1,
		const void* kidnergarten2);
int compareByKindergartenTypeAndNumOfChildren(const void* kidnergarten1,
		const void* kidnergarten2);
void SortKindergartenByChildrenID(Garden** pGardenList, int count);

#endif
