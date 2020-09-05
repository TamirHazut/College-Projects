#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GeneralFunc.h"

FILE* openFile(const char *filename, const char *permission) {
	FILE *file = fopen(filename, permission);
	if (!file) {
		fprintf(stderr, "Could not open file: %s\n", filename);
		exit(1);
	}
	return file;
}

ScoreWeight readWeightFromFile(FILE *file) {
	ScoreWeight weight;
	char c;
	if (fscanf(file, "%f%f%f%f", &weight.w1, &weight.w2, &weight.w3, &weight.w4)
			!= TOTAL_SCORE_WEIGHTS) {
		fprintf(stderr, "line %d: Cannot read from file.", __LINE__);
		exit(1);
	}
	while ((c = fgetc(file)) != '\n');
	return weight;
}

Sequence readSequenceFromFile(FILE *file, int isMainSequence) {
	Sequence sequence;
	int maxChars;
	maxChars = (isMainSequence ? MAX_MAIN_SEQUENCE_LENGTH : MAX_SEQUNECE_LENGTH);
	sequence.length = 0;
	char temp[maxChars];

	// Reading the entire sequence from the file
	if (fgets(temp, maxChars, file) != NULL)
	{
		// Removing all unwanted characters, such as: "\n", "\r"
		temp[strcspn(temp, "\r\n")] = '\0';
		sequence.length = strlen(temp);
		sequence.seq = strdup(temp);
	}
	return sequence;
}

int readNumberOfSequencesToComapre(FILE *file) {
	int num;
	char c;
	if (fscanf(file, "%d", &num) != 1) {
		fprintf(stderr, "line %d: Cannot read from file.", __LINE__);
		exit(1);
	}
	while ((c = fgetc(file)) != '\n');
	return num;
}

int searchForCharInString(const char* string, char c)
{
	int i;
	for (i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == c)
		{
			return 1;
		}
	}
	return 0;
}

int searchCharsInGroup(const char** group, int groupSize, char c1, char c2)
{
	int c1Found, c2Found, i;
	for (i = 0; i < groupSize; i++)
	{
		c1Found = 0;
		c2Found = 0;
		c1Found = searchForCharInString(group[i], c1);
		if (c1Found) { // Only if the first char found search for the second char
			c2Found = searchForCharInString(group[i], c2);
			if (c2Found)
			{
				return 1;
			}
		}
	}
	return 0;
}

/*
* Creating a Matrix of 25x25 for quering at O(1) a 2 char compare
* Each cell will hold a float value of the score weight according to the signs ('*', ':', '.', ' ')
* which represents if both chars that create those matrix coordinates
* Are the same ('*')
* Are at the same conservative group (':')
* Are at the same semi conservative group ('.')
* Have no connection at all (' ')
*/
float* createCompareTable(ScoreWeight weight) {
    int i, j, numberOfConservativeGroups, numberOfSemiConservativeGroups;
	float* compareTable;
	numberOfConservativeGroups = 9;
	const char *conservativeGroups[9] = {"NDEQ", "NEQK", "STA", "MILV", "QHRK", "NHQK", "FYW", "HY", "MILF"}; 
	numberOfSemiConservativeGroups = 11;
	const char *semiConservativeGroups[11] = {"SAG", "ATV", "CSA", "SGND", "STPA", "STNK", "NEQHRK", "NDEQHK", "SNDEQK", "HFY", "FVLIM"};
	
	compareTable = (float*) malloc(sizeof(float)*COMPARE_TABLE_SIZE*COMPARE_TABLE_SIZE);
	if (!compareTable) {
		fprintf(stderr, "Could not allocate compareTable\n");
		exit(1);
	}
	memset(compareTable, 0, COMPARE_TABLE_SIZE*COMPARE_TABLE_SIZE); // Reseting all cells to be 0
	for (i = 0; i < COMPARE_TABLE_SIZE; i++) {
		for (j = 0; j <= i; j++) { // Running only on half of the matrix since it is a symmetric matrix
			if (i == j) {
				*(compareTable + i*COMPARE_TABLE_SIZE + j) = weight.w1;
			} else if ( (searchCharsInGroup(conservativeGroups, numberOfConservativeGroups, (char)(i+'A'), (char)(j+'A'))) && (*(compareTable + i*COMPARE_TABLE_SIZE + j) == 0) ) {
				*(compareTable + i*COMPARE_TABLE_SIZE + j) = -weight.w2;
				*(compareTable + j*COMPARE_TABLE_SIZE + i) = -weight.w2;
			} else if ( (searchCharsInGroup(semiConservativeGroups, numberOfSemiConservativeGroups, (char)(i+'A'), (char)(j+'A'))) && (*(compareTable + i*COMPARE_TABLE_SIZE + j) == 0) )  {
				*(compareTable + i*COMPARE_TABLE_SIZE + j) = -weight.w3;
				*(compareTable + j*COMPARE_TABLE_SIZE + i) = -weight.w3;
			} else {
				*(compareTable + i*COMPARE_TABLE_SIZE + j) = -weight.w4;
				*(compareTable + j*COMPARE_TABLE_SIZE + i) = -weight.w4;
			}
		}
	}
	return compareTable;
}


void writeToFileComparisonResult(FILE *file, BestMatch result) {
	fprintf(file, "%d %d\n", result.offset, result.mutantIndex);
}


