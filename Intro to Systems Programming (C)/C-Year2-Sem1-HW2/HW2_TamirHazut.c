/*
 * HW2_TamirHazut.c
 *
 *  Created on: Nov 28, 2018
 *      Author: tamir-ubuntu
 */

#include <stdio.h>
#include <stdlib.h>
#include "general_functions.h"

void printMenu() {
	printf("\n\n");
	printf("Please choose one of the following options\n");
	printf("%d - Enter new string\n", NEW_STRING);
	printf("%d - Print current string\n", CURRENT_STRING);
	printf("%d - Count words in string\n", COUNT_WORDS);
	printf("%d - Print longest word in string CAPITALIZED\n", LONGEST_WORD);
	printf("%d - Revert each word in string\n", REVERT_WORD);
	printf("%d - Check eraseCharsFromStr\n", CHECK_ERASE_CHARS);
	printf("%d - Check palindrome\n", CHECK_PALINDROME);
	printf("%d - Exit\n", EXIT);
}

void performChoice(int option, char *str) {
	getchar();
	switch (option) {
	case NEW_STRING:
		initString(str, MAX_LEN);
		break;

	case CURRENT_STRING:
		printString(str);
		break;

	case COUNT_WORDS: {
		int count = countWords(str);
		printf("There are %d words in string\n", count);
		break;
	}
	case LONGEST_WORD:
		longestInCaptital(str);
		printf("String after longest capital: %s\n", str);
		break;

	case REVERT_WORD:
		revertWords(str);
		printf("String after revert: %s\n", str);
		break;

	case CHECK_ERASE_CHARS:
		eraseCharsFromString(str, ":, ?!-;");
		printf("String after erase: %s\n", str);
		break;

	case CHECK_PALINDROME:
		if (isPalindrome(str))
			printf("String %s is palindrome\n", str);
		else
			printf("String %s is NOT palindrome\n", str);
		break;

	case EXIT:
		printf("Bye bye\n");
		break;

	default:
		printf("Wrong option\n");
		break;
	}

}
int main() {
	int option;
	char str[MAX_LEN] = "\0";

	do {
		printMenu();
		scanf("%d", &option);
		performChoice(option, str);

	} while (option != EXIT);

	return EXIT_SUCCESS;
}
