#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Child.h"
#include "General.h"

/**************************************************/
/*             Read a Child from a file           */
/**************************************************/
void readChildFromTextFile(FILE* fp, Child* pChild) {
	//Child ID
	fscanf(fp, "%d", &pChild->id);
	fscanf(fp, "%d", &pChild->age);
}
void readChildFromBinFile(FILE* fp, Child* pChild) {
	//Child ID
	unsigned char upperBits,lowerBits;
	int id,age,temp;
	fread(&lowerBits,sizeof(char),1,fp);
	fread(&upperBits,sizeof(char),1,fp);
	temp = 0;
	temp = upperBits & 0xFF;
	temp = temp << 8;
	temp = temp | lowerBits;

	id = temp & 0x1FFF;
	pChild->id = id;

	temp = temp >> 13;
	age = temp & 0x7;
	pChild->age = age;
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
void writeChildToTextFile(FILE* fp, const Child* pChild) {
	fprintf(fp, "%d %d\n", pChild->id, pChild->age);
}
void writeChildToBinFile(FILE* fp, const Child* pChild) {
	unsigned char upperBits,lowerBits;
	int temp;
	temp = 0;
	temp = pChild->age & 0x7;
	temp = temp << 13;
	temp = temp | pChild->id;
	lowerBits = temp & 0xFF;
	temp = temp >> 8;
	upperBits = temp & 0xFF;
	fwrite(&lowerBits,sizeof(char),1,fp);
	fwrite(&upperBits,sizeof(char),1,fp);
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
