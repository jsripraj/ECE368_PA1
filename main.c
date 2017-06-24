#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

int main(int argc, char **argv) {
	if (argc != 5) {
		printf("Not enough arguments");
		return EXIT_FAILURE;
	}
	int Size = 0; // Number of elements in Array
	long * Array = Load_From_File(argv[2], &Size);
	for (int i = 0; i < Size; i++) {
		printf("\n%ld", Array[i]);
	}
	int nels = Save_To_File(argv[4], Array, Size);
	printf("\nnels = %d\n", nels);
	return 0;
}
