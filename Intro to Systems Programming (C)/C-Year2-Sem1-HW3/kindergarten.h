/*
 * kindergarden.h
 *
 *  Created on: Dec 12, 2018
 *      Author: tamir-ubuntu
 */

#ifndef KINDERGARTEN_H_
#define KINDERGARTEN_H_

#define MAX_AGE_FOR_CHOVA 5

#include "kid.h"

typedef enum {
	Chova, TromChova, TromTromChova, NumOfKindergartenTypes
} KindergartenType;

typedef struct {
	char* name;
	int kindergartenType;
	int numOfKids;
	Kid** kids;
} Kindergarten;

void showKindergarten(const Kindergarten* kindergarten);
void saveKindergarten(FILE *file, const Kindergarten* kindergarten);
void readKindergarten(FILE *file, Kindergarten* kindergarten);
int initKindergarten(Kindergarten* kindergarten);
int countChovaInKindergarten(Kindergarten* kindergarten);
void startKindergarten(Kindergarten* kindergarten, char* name);
void printGardenTypes();
int isAValidType(int type);
void addKids(Kindergarten* kindergarten);
void addSpecificKid(Kindergarten* kindergarten, int index);
int checkID(Kindergarten* kindergarten, int id);
void releaseKindergarten(Kindergarten* kindergarten);
char* getKindergartenName(FILE *file);
void findKid(Kindergarten* kindergarten);
#endif /* KINDERGARTEN_H_ */
