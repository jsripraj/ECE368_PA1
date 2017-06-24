#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

long * Load_From_File(char * Filename, int * Size) {
	FILE * inf = fopen(Filename, "r");
	// Determine how many longs (4 bytes each) are in file
	fseek(inf, 0, SEEK_END);
	long len = ftell(inf);
	* Size = (int)(len / sizeof(long));
	
	// Allocate memory to store data from file
	long * Array = malloc(len);
	
	// Read data into array
	fseek(inf, 0, SEEK_SET);
	fread(Array, sizeof(long), *Size, inf);
	fclose(inf);
	return Array;
}

int Save_To_File(char * Filename, long * Array, int Size) {
	FILE * outf = fopen(Filename, "w");
	int nels = fwrite(Array, sizeof(long), Size, outf);
	fclose(outf);
	return nels;
}

int * Get_Seq(int Size, int *Seq_Nels) {
	int q = 0, row = 0, i = 0;
	int t1 = 1, t2 = 1;
	while(t1 * t2 < Size) {
		if (q == row) {
			row++;
			q = 0;
			t2 = 1;
			for (t1 = 1, i = 0; i < row; i++) { t1 *= 2; }
		} else {
			q++;
			t1 /= 2;
			t2 *= 3;
		}
		(*Seq_Nels)++;
	}
	int *seq = malloc((*Seq_Nels) * sizeof(int));	
	int index = 0;
	i = 0; q = 0; row = 0; t1 = 1; t2 = 1;
	while(t1 * t2 < Size) {
		seq[index] = t1 * t2;
		if (q == row) { 
			row++; 
			q = 0;
			t2 = 1;
			for (t1 = 1, i = 0; i < row; i++) { t1 *= 2; }
		} else {
			q++;
			t1 /= 2;
			t2 *= 3;
		}
		index++;
	}
	return seq;
}

/*
void Shell_Insertion_Sort(long * Array, int Size, double * N_Comp, double * N_Move) {

}

void Shell_Insertion_Sort(long * Array, int Size, double * N_Comp, double * N_Move) {

}
*/

int Print_Seq(char * Filename, int Size) {
	FILE * fp = fopen(Filename, "w");
	int seq_nels = 0;
	int * seq = Get_Seq(Size, &seq_nels);
	for (int i = 0; i < seq_nels; i++) {
		fprintf(fp, "%d\n", seq[i]);
	}
	fclose(fp);
	return seq_nels;
}
