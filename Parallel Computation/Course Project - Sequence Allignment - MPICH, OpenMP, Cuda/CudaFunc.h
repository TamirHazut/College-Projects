#ifndef CUDAFUNC_H_
#define CUDAFUNC_H_

#include "GeneralFunc.h"

void *allocateDeviceMemory(int size);
void copyToMemory(void* to, void* from, int size, int dir);
void freeDeviceMemory(void* memory);

BestMatch findBestMatchingComparison(Sequence sequence1, Sequence sequence2, float* compareTable, int lowOffset, int highOffset, ScoreWeight weight);

#endif /* CUDAFUNC_H_ */

