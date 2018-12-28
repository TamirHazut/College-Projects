/*
 * city.c
 *
 *  Created on: Dec 12, 2018
 *      Author: tamir-ubuntu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city.h"

/* Menu Functions */
void readCity(City* city) {
	int i;
	FILE *file;
	file = fopen(FILE_NAME, "r");
	if (file != NULL) {
		ReleaseCity(city);
		fscanf(file, "%d", &(city->numOfKindergartens));
		if (!initCity(city)) {
			return;
		}
		for (i = 0; i < city->numOfKindergartens; i++) {
			readKindergarten(file, city->kindergartens[i]);
		}
	}
	fclose(file);
}

void showCityGardens(const City* city) {
	int i;
	for (i = 0; i < city->numOfKindergartens; i++) {
		printf("Kindergarten %d:\n", i + 1);
		showKindergarten(city->kindergartens[i]);
	}
}

void showSpecificGardenInCity(const City* city) {
	if (city->numOfKindergartens > 0) {
		int kindergartenNum;
		kindergartenNum = isAKindergarten(stdin, city);
		if (kindergartenNum != -1) {
			showKindergarten(city->kindergartens[kindergartenNum]);
		} else {
			printf("No such Kindergarten.\n");
		}
	} else {
		printf("There are no kindergartens in this city.");
	}
}

void saveCity(const City* city) {
	int i;
	FILE *file;
	file = fopen(FILE_NAME, "w");
	if (file != NULL) {
		fprintf(file, "%d\n", city->numOfKindergartens);
		for (i = 0; i < city->numOfKindergartens; i++) {
			saveKindergarten(file, city->kindergartens[i]);
		}
	}
	fclose(file);
}

void cityAddGarden(City* city) {
	char* nameToAdd;
	int alreadyHaveThisKindergarten;
	printf("Name:\n");
	nameToAdd = getKindergartenName(stdin);
	alreadyHaveThisKindergarten = searchForKindergarten(city, nameToAdd);
	if (alreadyHaveThisKindergarten == -1) {
		if (!reallocKindergartens(city)) {
			return;
		}
		startKindergarten(city->kindergartens[city->numOfKindergartens],
				nameToAdd);
		city->numOfKindergartens++;
	} else {
		printf("This kindergarten already in list.");
	}
}

void addChildToSpecificGardenInCity(City* city) {
	int kindergartenNum;
	kindergartenNum = isAKindergarten(stdin, city);
	if (kindergartenNum == -1 || !reallocKids(city, kindergartenNum)) {
		printf("No such Kindergarten.\n");
		return;
	}
	addSpecificKid(city->kindergartens[kindergartenNum],
			city->kindergartens[kindergartenNum]->numOfKids);
	city->kindergartens[kindergartenNum]->numOfKids++;
}

void birthdayToChild(City* city) {
	if (city->numOfKindergartens > 0) {
		int kindergartenNum;
		kindergartenNum = isAKindergarten(stdin, city);
		if (kindergartenNum != -1) {
			findKid(city->kindergartens[kindergartenNum]);
		} else {
			printf("No such Kindergarten.\n");
		}
	} else {
		printf("There are no kindergartens in this city.");
	}
}

int countChova(City* city) {
	int i, cityChovaCounter;
	cityChovaCounter = 0;
	for (i = 0; i < city->numOfKindergartens; i++) {
		if (city->kindergartens[i]->kindergartenType == 0) {
			cityChovaCounter += countChovaInKindergarten(
					city->kindergartens[i]);
		}
	}
	return cityChovaCounter;
}

/* My Functions */
int searchForKindergarten(const City* city, char* nameToSearch) {
	int i;
	for (i = 0; i < city->numOfKindergartens; i++) {
		if (strcmp(nameToSearch, (city->kindergartens[i])->name) == 0) {
			return i;
		}
	}
	return -1;
}
int isAKindergarten(FILE* file, const City* city) {
	char* nameToSearch;
	int found;
	printf("Give me the Kindergarten Name:\n");
	nameToSearch = getKindergartenName(file);
	found = searchForKindergarten(city, nameToSearch);
	free(nameToSearch);
	return found;
}

/* Init */
int initCity(City* city) {
	int i;
	city->kindergartens = (Kindergarten**) malloc(
			city->numOfKindergartens * sizeof(Kindergarten*));
	if (!city->kindergartens) {
		return 0;
	}
	for (i = 0; i < city->numOfKindergartens; i++) {
		initKindergartensArray(city, i);
	}
	return 1;
}
int initKindergartensArray(City* city, int index) {
	city->kindergartens[index] = (Kindergarten*) malloc(sizeof(Kindergarten));
	if (!city->kindergartens[index]) {
		return 0;
	}
	return 1;
}

/* Realloc */
int reallocKindergartens(City* city) {
	city->kindergartens = (Kindergarten**) realloc(city->kindergartens,
			(city->numOfKindergartens + 1) * sizeof(Kindergarten*));
	if (!city->kindergartens) {
		return 0;
	}
	city->kindergartens[city->numOfKindergartens] = (Kindergarten*) malloc(
			sizeof(Kindergarten));
	if (!city->kindergartens[city->numOfKindergartens]) {
		return 0;
	}
	return 1;
}

int reallocKids(City* city, int index) {
	city->kindergartens[index]->kids = (Kid**) realloc(
			city->kindergartens[index]->kids,
			sizeof(Kid*) * (city->kindergartens[index]->numOfKids + 1));
	if (!city->kindergartens[index]->kids) {
		return 0;
	}
	city->kindergartens[index]->kids[city->kindergartens[index]->numOfKids] =
			(Kid*) calloc(1, sizeof(Kid));
	if (!city->kindergartens[index]->kids[city->kindergartens[index]->numOfKids]) {
		return 0;
	}
	return 1;
}

/* Free */
void ReleaseCity(City* city) {
	int i;
	for (i = 0; i < city->numOfKindergartens; i++) {
		releaseKindergarten(city->kindergartens[i]);
	}
	free(city->kindergartens);
}

