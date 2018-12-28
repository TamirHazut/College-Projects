/*
 * general_functions.h
 *
 *  Created on: Nov 28, 2018
 *      Author: tamir-ubuntu
 */

#ifndef GENERAL_FUNCTIONS_H_
#define GENERAL_FUNCTIONS_H_

#define  NEW_STRING 		1
#define  CURRENT_STRING 	2
#define  COUNT_WORDS 	3
#define  LONGEST_WORD 	4
#define  REVERT_WORD 	5
#define  CHECK_ERASE_CHARS 6
#define  CHECK_PALINDROME 	7
#define  EXIT 			-1
#define  MAX_LEN	      100

void initString(char* str, int maxLength);
void printString(const char* str);
void clearNewLine(char* string,int size);
int countWords(char* str);
void longestInCaptital(char* str);
void findLongestWord(char* str, char* longestWord);
void switchToNewDelimiter(char* str, char* newDelimiter);
int isSpecialDelimiter(char c);
void revertWords(char* str);
void reverseWords(char* str, char* delimiter);
void eraseCharsFromString(char* str, const char* symbols);
int isPalindrome(const char *str);
void stringCleaner(char* str, char* cleanString);

#endif /* GENERAL_FUNCTIONS_H_ */
