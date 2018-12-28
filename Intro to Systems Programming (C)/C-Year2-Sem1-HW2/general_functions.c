/*
 * general_functions.c
 *
 *  Created on: Nov 28, 2018
 *      Author: tamir-ubuntu
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "general_functions.h"

#define NUM_OF_SPECIAL_DELIMITERS 5
char specialDelimiters[] = " ,:?-";

void initString(char* str, int maxLength) {
	printf("\nPlease enter a string (Max length: %d characters):\n",
	MAX_LEN - 1);
	fgets(str, maxLength, stdin);
	clearNewLine(str, strlen(str));
}

void printString(const char* str) {
	printf("\nThe string is:\n%s", str);
}
void clearNewLine(char* string, int size) {
	if (string[size - 1] == '\n') {
		string[size - 1] = '\0';
	}
}
int countWords(char* str) {
	char strCopy[strlen(str)], *token;
	int wordCounter;
	strcpy(strCopy, str);
	token = strtok(strCopy, specialDelimiters);
	wordCounter = 0;
	while (token) {
		wordCounter++;
		token = strtok(NULL, specialDelimiters);
	}
	return wordCounter;
}
void findLongestWord(char* str, char* longestWord) {
	char strCopy[strlen(str)], *token;
	int currentLength, longestLength;
	strcpy(strCopy, str);
	token = strtok(strCopy, specialDelimiters);
	while (token) {
		currentLength = strlen(token);
		if (currentLength > longestLength) {
			longestLength = currentLength;
			strcpy(longestWord, token);
		}
		token = strtok(NULL, specialDelimiters);
	}
}
void longestInCaptital(char* str) {
	char longestWord[strlen(str)];
	findLongestWord(str, longestWord);
	str = strstr(str, longestWord);
	char *temp = longestWord;
	while (*(temp++)) {
		*str = toupper(*str);
		str++;
	}
}
int isSpecialDelimiter(char c) {
	int i;
	for (i = 0; i < NUM_OF_SPECIAL_DELIMITERS; i++) {
		if (specialDelimiters[i] == c) {
			return 1;
		}
	}
	return 0;
}
void switchToNewDelimiter(char* str, char* newDelimiter) {
	int i;
	for (i = 0; i < strlen(str); i++) {
		if (isSpecialDelimiter(str[i])) {
			str[i] = *newDelimiter;
		}
	}
}
void reverseWords(char* str, char* delimiter) {
	char strCopy[strlen(str)], *token;
	int i;
	strcpy(strCopy, str);
	token = strtok(strCopy, delimiter);
	while (token) {
		while (*str == *delimiter) {
			str++;
		}
		for (i = strlen(token) - 1; i >= 0; i--) {
			*str = token[i];
			str++;
		}
		token = strtok(NULL, delimiter);
	}
}
void revertWords(char* str) {
	char newDelimiter[] = "*";
	switchToNewDelimiter(str, newDelimiter);
	reverseWords(str, newDelimiter);
}
void eraseCharsFromString(char* str, const char* symbols) {
	char strCopy[strlen(str)], newStr[strlen(str)], *token;
	strcpy(strCopy, str);
	token = strtok(strCopy, symbols);
	while (token) {
		strcat(newStr, token);
		token = strtok(NULL, symbols);
	}
	strcpy(str, newStr);
}
void stringCleaner(char* str, char* cleanString) {
	while (*str) {
		if (isalpha((*str))) {
			*cleanString = tolower(*str);
			cleanString++;
		}
		str++;
	}
}
int isPalindrome(const char *str) {
	char strCopy[strlen(str)], temp[strlen(str)], delimiter[] = "";
	strcpy(strCopy, str);
	stringCleaner(strCopy, temp);
	strcpy(strCopy, temp);
	reverseWords(temp, delimiter);
	return (strcmp(strCopy, temp) == 0 ? 1 : 0);
}
