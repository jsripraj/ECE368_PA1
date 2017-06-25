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
	int q = 0, row = 0, i = 0; // q is from 3^q, row is "pyramid" row
	int t1 = 1, t2 = 1; // t1 is first term (2^p), t2 is second term (3^q)
	while(t1 * t2 < Size) {
		if (q == row) { // Moving to next row, so reset t1 and t2
			row++;
			q = 0;
			t2 = 1;
			for (t1 = 1, i = 0; i < row; i++) { t1 *= 2; }
		} else { // Moving along row, t1 and t2 change powers
			q++;
			t1 /= 2;
			t2 *= 3;
		}
		(*Seq_Nels)++; // Keep track of elements in sequence
	}
	int *seq = malloc((*Seq_Nels) * sizeof(int));
	int index = 0;
	i = 0; q = 0; row = 0; t1 = 1; t2 = 1;
	// Same algorithm. But this time store the sequence in the array
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

void Shell_Insertion_Sort(long * Array, int Size, double * N_Comp, double * N_Move) {
	int i, j, k, x, seq_nels = 0;
	long temp;
	// Generate sequence
	int * seq = Get_Seq(Size, &seq_nels);
	// For each element in sequence (going backwards towards 1)...
	for (i = seq_nels - 1; i >= 0; i--) {
		// For each "column" in shell sort...
		for (j = 0; j < seq[i]; j++) {
			// For each "insertion" in insertion sort...
			for (k = j + seq[i]; k < Size; k += seq[i]) {
				x = k;
				do {
					printf("\nx = %d, Array[0] = %ld", x, Array[0]);
					(*N_Comp)++;
					// Swap until correct position or break out
					if (Array[x] < Array[x - seq[i]]) {
						temp = Array[x];
						Array[x] = Array[x - seq[i]];
						Array[x - seq[i]] = temp;
						(*N_Move) += 3;
						x -= seq[i];
					} else {
						x = -1;
					}
				} while (x - seq[i] >= 0);
			}
		}
	}
	free(seq);
	return;
}

void Shell_Selection_Sort(long * Array, int Size, double * N_Comp, double * N_Move) {
	int i, j, k, min, x; // min is the index of the lowest number found
	long temp;
	// Generate sequence
	int seq_nels = 0;
	int *seq = Get_Seq(Size, &seq_nels);
	// For each number in sequence (going backwards)...
	for (i = seq_nels - 1; i >= 0; i--) {
		// For each "column" in shell sort...
		for (j = 0; j < seq[i]; j++) {
			// For each number in column
			for (k = j; k < Size; k += seq[i]) {
				// Find the index of the minimum number
				min = k;
				for (x = k + seq[i]; x < Size; x += seq[i]) {
					(*N_Comp)++;
					if (Array[x] < Array[min]) {
						min = x;
					}
				}
				// Swap the numbers at the cursor and min indexes
				if (min != k) {
					(*N_Move) += 3;
					temp = Array[k];
					Array[k] = Array[min];
					Array[min] = temp;
				}
			}
		}
	}
	free(seq);
	return;
}

int Print_Seq(char * Filename, int Size) {
	FILE * fp = fopen(Filename, "w");
	int seq_nels = 0;
	// Generate the sequence
	int * seq = Get_Seq(Size, &seq_nels);
	// Write to file
	for (int i = 0; i < seq_nels; i++) {
		fprintf(fp, "%d\n", seq[i]);
	}
	fclose(fp);
	free(seq);
	return seq_nels;
}
