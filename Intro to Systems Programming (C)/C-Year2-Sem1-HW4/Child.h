#ifndef __CHILD__
#define __CHILD__

typedef struct {
	int id;
	int age;
} Child;

void readChildFromTextFile(FILE* fp, Child* pChild);
void readChildFromBinFile(FILE* fp, Child* pChild);
void getChildFromUser(Child* pChild, int id);
void showChild(const Child* pChild);
void writeChildToTextFile(FILE* fp, const Child* pChild);
void writeChildToBinFile(FILE* fp, const Child* pChild);
int findChildById(Child** pChildList, int count, int id);
void birthday(Child* pChild);
int compareByChildrenID(const void* child1, const void* child2);
//void	releaseChild(Child* pChild);
#endif
