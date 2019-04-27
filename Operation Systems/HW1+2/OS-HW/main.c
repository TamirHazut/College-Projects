#include <stdio.h>
#include <stdlib.h>
#include "hw1.h"
#include "hw2.h"


int main(int argc, char* argv[]) {
	get_board_for_threads(argc, argv);
	get_board_for_processes(argc, argv);
	return EXIT_SUCCESS;
}
