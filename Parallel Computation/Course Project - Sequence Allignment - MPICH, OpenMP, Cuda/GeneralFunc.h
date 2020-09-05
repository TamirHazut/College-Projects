#ifndef SEQUENCEFUNC_H_
#define SEQUENCEFUNC_H_

#define COMPARE_TABLE_SIZE 26
#define MAX_MAIN_SEQUENCE_LENGTH 3000
#define MAX_SEQUNECE_LENGTH 2000
#define TOTAL_SCORE_WEIGHTS 4
#define OUTPUT_FILE "output.txt"

typedef struct {
	float w1;
	float w2;
	float w3;
	float w4;
} ScoreWeight;

typedef struct {
	char *seq;
	int length;
} Sequence;

typedef struct {
	int offset;
	int mutantIndex;
	double score;
} BestMatch;

FILE* openFile(const char* filename, const char* permission);

ScoreWeight readWeightFromFile(FILE *file);
Sequence readSequenceFromFile(FILE *file, int isMainSequence);
int readNumberOfSequencesToComapre(FILE *file);

int searchForCharInString(const char* string, char c);
int searchCharsInGroup(const char** group, int groupSize, char c1, char c2);
float* createCompareTable(ScoreWeight weight);

void writeToFileComparisonResult(FILE *file, BestMatch result);

#endif /* SEQUENCEFUNC_H_ */

