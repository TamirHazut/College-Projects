/*
 * kid.c
 *
 *  Created on: Dec 12, 2018
 *      Author: tamir-ubuntu
 */

#include "kid.h"
#include "general_functions.h"

void showKid(const Kid* kid) {
	printf("ID:%d\tAge:%d.\n", kid->id, kid->age);
}
void readKid(FILE *file, Kid* kid) {
	if (file != NULL) {
		fscanf(file, "%d %d", &(kid->id), &(kid->age));
	}
}
void saveKid(FILE *file, const Kid* kid) {
	fprintf(file,"%d %d\n", kid->id, kid->age);
}
void addKid(Kid* kid) {
	printf("Age:\n");
	scanf("%d", &(kid->age));
}
