/*
 * picture_manipulation.h
 *
 *  Created on: Nov 11, 2018
 *      Author: tamir-ubuntu
 */

#ifndef PICTURE_MANIPULATION_H_
#define PICTURE_MANIPULATION_H_
#include "general_functions.h"

void startPictureManipulating(int* mat, int size);
void pictureManipulationMenu(int* mat, int size);
void showPictureManipulationMenuMessage();
void checkPictureManipulationChoice(int* mat, int rows, int cols, int choice,
		boolean* leave);
void change90Degree(int* mat, int rows, int cols, int clockwise);
void transpose(int* mat, int rows, int cols);
void flipVertical(int* mat, int rows, int cols);
void flipHorizontal(int* mat, int rows, int cols);

#endif /* PICTURE_MANIPULATION_H_ */
