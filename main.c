#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

int main(int argc, char **argv) {
	if (argc != 5) {
		printf("Not enough arguments");
		return EXIT_FAILURE;
	}
	int Size = 0; // Number of elements in Array

	// Load elements from file into an array
	long * Array = Load_From_File(argv[2], &Size);
	printf("\nArray:");
	for (int i = 0; i < Size; i++) {
		printf("\n%ld", Array[i]);
	}
	
	// Print out the sequence
	Print_Seq(argv[3], Size);	

	// Write the elements from array into file
	int nels = Save_To_File(argv[4], Array, Size);
	printf("\nSize = %d\n", nels);
	return 0;
}
