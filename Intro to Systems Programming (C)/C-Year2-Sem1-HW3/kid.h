/*
 * kid.h
 *
 *  Created on: Dec 12, 2018
 *      Author: tamir-ubuntu
 */

#ifndef KID_H_
#define KID_H_
#include <stdio.h>

typedef struct {
	int id;
	int age;
} Kid;
void showKid(const Kid* kid);
void saveKid(FILE *file, const Kid* kid);
void readKid(FILE *file, Kid* kid);
void addKid(Kid* kid);

#endif /* KID_H_ */
