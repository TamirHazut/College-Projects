#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Child.h"
#include "General.h"

/**************************************************/
/*             Read a Child from a file           */
/**************************************************/
void readChild(FILE* fp, Child* pChild) {
	//Child ID
	fscanf(fp, "%d", &pChild->id);
	fscanf(fp, "%d", &pChild->age);
}

/**************************************************/
/*            show a Child				           */
/**************************************************/
void showChild(const Child* pChild) {
	printf("\nID:%d  ", pChild->id);
	printf("Age:%d  ", pChild->age);
}

/**************************************************/
void getChildFromUser(Child* pChild, int id)
/**************************************************/
/**************************************************/
{
	pChild->id = id;

	puts("\nAge:\t");
	scanf("%d", &pChild->age);
}

/**************************************************/
/*Write a Child to the open file				*/
/**************************************************/
void writeChild(FILE* fp, const Child* pChild) {
	fprintf(fp, "%d %d\n", pChild->id, pChild->age);
}

//linear search
int findChildById(Child** pChildList, int count, int id) {
	int index;
	Child** found = NULL;
	Child tempChild = { id, 0 };
	Child* temp = &tempChild;
	qsort(pChildList, count, sizeof(Child*), compareByChildrenID);
	found = (Child**) bsearch(&temp, pChildList, count, sizeof(Child*),
			compareByChildrenID);
	if (found == NULL) {
		return -1;
	} else {
		index = found - pChildList;
		return index;
	}
}

void birthday(Child* pChild) {
	pChild->age++;
}

int compareByChildrenID(const void* child1, const void* child2) {
	Child* c1 = *(Child**) child1;
	Child* c2 = *(Child**) child2;
	return (c1->id - c2->id);
}
//void	releaseChild(Child* pChild)
//{
//	//nothing to release
//}
