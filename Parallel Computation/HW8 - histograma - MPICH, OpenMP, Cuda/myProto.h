#pragma once

#include <stdio.h>

#define BUCKET_SIZE 256

int readSizeFromFile(FILE *file);
int* readArrFromFile(FILE *file, int size);
FILE* openFile(char *filename);

int* calcHistogram(int* arr, int size);

int* histogramUsingOpenMP(int* arr, int size);
int* histogramUsingCuda(int* arr, int size);

void test(int *data, int n);
int computeOnGPU(int *data, int n);
