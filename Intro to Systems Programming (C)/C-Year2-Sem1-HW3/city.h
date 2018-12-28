/*
 * city.h
 *
 *  Created on: Dec 12, 2018
 *      Author: tamir-ubuntu
 */

#ifndef CITY_H_
#define CITY_H_

#include "kindergarten.h"

#define FILE_NAME "DataFile.txt"

typedef struct {
	Kindergarten** kindergartens;
	int numOfKindergartens;
} City;

void readCity(City* city);
void showCityGardens(const City* city);
void showSpecificGardenInCity(const City* city);
void saveCity(const City* city);
void cityAddGarden(City* city);
void addChildToSpecificGardenInCity(City* city);
void birthdayToChild(City* city);
int countChova(City* city);

int searchForKindergarten(const City* city, char* nameToSearch);
int isAKindergarten(FILE* file, const City* city);

int initCity(City* city);
int initKindergartensArray(City* city, int index);
int reallocKindergartens(City* city);
int reallocKids(City* city, int index);

void ReleaseCity(City* city);

#endif /* CITY_H_ */
