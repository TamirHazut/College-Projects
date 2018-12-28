/*
 * kindergarden.c
 *
 *  Created on: Dec 12, 2018
 *      Author: tamir-ubuntu
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "kindergarten.h"

const char* kindergatenTypes[NumOfKindergartenTypes] = { "Chova", "Trom Chova",
		"Trom Trom Chova" };

void showKindergarten(const Kindergarten* kindergarten) {
	int i;
	printf("Name:%s\tType:%s\tChildren:%d\n", kindergarten->name,
			kindergatenTypes[kindergarten->kindergartenType],
			kindergarten->numOfKids);
	for (i = 0; i < kindergarten->numOfKids; i++) {
		showKid(kindergarten->kids[i]);
	}
}

char* getKindergartenName(FILE *file) {
	char *temp;
	int physSize, logicSize, c;
	physSize = 2;
	logicSize = 0;
	temp = (char*) calloc(physSize, sizeof(char));
	if (!temp) {
		return NULL;
	}
	while ((c = fgetc(file)) != (file == stdin ? '\n' : ' ')) {
		if (physSize == logicSize) {
			physSize *= 2;
			temp = (char*) realloc(temp, physSize * sizeof(char));
		}
		if (!(isspace(c))) {
			*(temp + logicSize) = c;
			logicSize++;
		}
	}
	return temp;
}

void readKindergarten(FILE *file, Kindergarten* kindergarten) {
	if (file != NULL) {
		int i;
		kindergarten->name = getKindergartenName(file);
		fscanf(file, "%d %d", &(kindergarten->kindergartenType),
				&(kindergarten->numOfKids));
		if (!initKindergarten(kindergarten)) {
			return;
		}
		for (i = 0; i < kindergarten->numOfKids; i++) {
			readKid(file, kindergarten->kids[i]);
		}
		getc(file);
	}
}
int initKindergarten(Kindergarten* kindergarten) {
	int i;
	kindergarten->kids = (Kid**) malloc(sizeof(Kid*) * kindergarten->numOfKids);
	if (!kindergarten->kids) {
		return 0;
	}
	for (i = 0; i < kindergarten->numOfKids; i++) {
		kindergarten->kids[i] = (Kid*) malloc(sizeof(Kid));
		if (!kindergarten->kids[i]) {
			return 0;
		}
	}
	return 1;
}
void saveKindergarten(FILE *file, const Kindergarten* kindergarten) {
	int i;
	fprintf(file, "%s %d %d\n", kindergarten->name,
			kindergarten->kindergartenType, kindergarten->numOfKids);
	for (i = 0; i < kindergarten->numOfKids; i++) {
		saveKid(file, kindergarten->kids[i]);
	}
}
int countChovaInKindergarten(Kindergarten* kindergarten) {
	int i, kindergartenChovaCounter;
	kindergartenChovaCounter = 0;
	for (i = 0; i < kindergarten->numOfKids; i++) {
		if (kindergarten->kids[i]->age >= MAX_AGE_FOR_CHOVA) {
			kindergartenChovaCounter++;
		}
	}
	return kindergartenChovaCounter;
}

void startKindergarten(Kindergarten* kindergarten, char* name) {
	int kindergartenType, numOfKids;
	kindergartenType = -1;
	kindergarten->name = name;
	do {
		printGardenTypes();
		scanf("%d", &kindergartenType);
	} while (!(isAValidType(kindergartenType)));
	kindergarten->kindergartenType = kindergartenType;
	printf("Children count:\n");
	scanf("%d", &numOfKids);
	kindergarten->numOfKids = numOfKids;
	if (numOfKids > 0) {
		printf("Enter children Details:\n");
		if (!initKindergarten(kindergarten)) {
			return;
		}
		addKids(kindergarten);
	}
}
void printGardenTypes() {
	int i;
	printf("Garden type:\n");
	for (i = 0; i < NumOfKindergartenTypes;i++) {
		printf("Enter %d for %s.\n",i,kindergatenTypes[i]);
	}
}
int isAValidType(int type) {
	if ((type == Chova) || (type == TromChova) || (type == TromTromChova)) {
		return 1;
	}
	printf("Invalid Type.\n");
	return 0;
}

void addKids(Kindergarten* kindergarten) {
	int i;
	for (i = 0; i < kindergarten->numOfKids; i++) {
		addSpecificKid(kindergarten, i);
	}
}
void addSpecificKid(Kindergarten* kindergarten, int index) {
	int id, isAlreadyInKindergarten;
	printf("ID No.:\n");
	scanf("%d", &id);
	isAlreadyInKindergarten = checkID(kindergarten, id);
	if (isAlreadyInKindergarten != -1) {
		printf("This child is in the Kindergarten.\n");
		return;
	}
	kindergarten->kids[index]->id = id;
	addKid(kindergarten->kids[index]);
}
int checkID(Kindergarten* kindergarten, int id) {
	int i;
	for (i = 0; i < kindergarten->numOfKids && kindergarten->kids[i] != NULL;
			i++) {
		if (id == kindergarten->kids[i]->id) {
			return i;
		}
	}
	return -1;
}
void findKid(Kindergarten* kindergarten) {
	int i, id;
	printf("ID No.:\n");
	scanf("%d", &id);
	i = checkID(kindergarten, id);
	if (i != -1) {
		kindergarten->kids[i]->age++;
	} else {
		printf("%d is not registered in this kindergarten", id);
	}
}
void releaseKindergarten(Kindergarten* kindergarten) {
	int i;
	for (i = 0; i < kindergarten->numOfKids; i++) {
		free(kindergarten->kids[i]);
	}
	free(kindergarten->name);
	free(kindergarten->kids);
}

