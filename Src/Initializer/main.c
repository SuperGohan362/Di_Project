#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if(argc < 5) {
		printf("Correct syntax is: %s -T1 fileName1 -T2 fileName2\n", argv[0]);
		exit(1);
	}
	char *fileName1, *fileName2;
	for(int i = 0; i < argc; i++) {
		if(!(strcmp(argv[i], "-T1"))) {
			fileName1 = malloc(strlen(argv[i + 1]) * sizeof(char));
			strcpy(fileName1, argv[i + 1]);
		} else if(!(strcmp(argv[i], "-T2"))) {
			fileName2 = malloc(strlen(argv[i + 1]) * sizeof(char));
			strcpy(fileName2, argv[i + 1]);
		}
	}

	FILE *fp_A = fopen(fileName1, "r");

	int elements = 0;
	int A_raws = 0;
	int c;
	do {
		c = fgetc(fp_A);
		if(feof(fp_A))
			break ;
		if(c == '\n') {
			A_raws++;
		} else if(c != ' ')
			elements++;
	} while(1);

	printf("Elements in A are %d\n", elements);
	printf("Raws in A are %d\n", A_raws);
	int A_columns = (int)elements / A_raws;
	printf("Columns in A are %d\n\n", A_columns);
	rewind(fp_A);

	//ALLOCATE A ARRAY
	uint8_t **A = malloc(A_raws * sizeof(char*));
	for(int i = 0; i < A_raws; i++)
		 A[i] = malloc(A_columns * sizeof(char));
	
	uint8_t **a = malloc(A_columns * sizeof(char*));
	for(int i = 0; i < A_columns; i++)
		 a[i] = malloc(A_raws * sizeof(char));

	//FILL A ARRAY
	for(int i = 0; i < A_raws; i++)
		for(int j = 0; j < A_columns; j++) 
			fscanf(fp_A, "%hhu", &A[i][j]);
	fclose(fp_A);


	FILE *fp_B = fopen(fileName2, "r");

	elements = 0;
	int B_raws = 0;
	do {
		c = fgetc(fp_B);
		if(feof(fp_B))
			break ;
		if(c == '\n') {
			B_raws++;
		} else if(c != ' ')
			elements++;
	} while(1);

	printf("Elements in B are %d\n", elements);
	printf("Raws in B are %d\n", B_raws);
	int B_columns = (int)elements / B_raws;
	printf("Columns line in B are %d\n\n", B_columns);
	rewind(fp_B);
	
	//ALLOCATE B ARRAY
	uint8_t **B = malloc(B_raws * sizeof(char*));
	for(int i = 0; i < B_raws; i++)
		 B[i] = malloc(B_columns * sizeof(char));
	
	uint8_t **b = malloc(B_columns * sizeof(char*));
	for(int i = 0; i < B_columns; i++)
		 b[i] = malloc(B_raws * sizeof(char));

	//FILL B ARRAY
	for(int i = 0; i < B_raws; i++)
		for(int j = 0; j < B_columns; j++)
			fscanf(fp_B, "%hhu", &B[i][j]);
	fclose(fp_B);
	free(fileName1);
	free(fileName2);


	for(int i = 0; i < A_raws; i++)
		for(int j = 0; j < A_columns; j++)
			a[j][i] = A[i][j];
	for(int i = 0; i < B_raws; i++)
		for(int j = 0; j < B_columns; j++)
			b[j][i] = B[i][j];

	//PRINT
	for(int i = 0; i < A_raws; i++) {
		for(int j = 0; j < A_columns; j++)
			printf("%d ", A[i][j]);
		printf("\n");
	}
	printf("\nReverted\n");
	for(int i = 0; i < A_columns; i++) {
		for(int j = 0; j < A_raws; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
	printf("\n\n");

	for(int i = 0; i < B_raws; i++) {
		for(int j = 0; j < B_columns; j++)
			printf("%d ", B[i][j]);
		printf("\n");
	}
	printf("\nReverted\n");
	for(int i = 0; i < B_columns; i++) {
		for(int j = 0; j < B_raws; j++)
			printf("%d ", b[i][j]);
		printf("\n");
	}
	
	//FREE
	for(int i = 0; i < A_columns; i++)
		free(a[i]);
	free(a);
	for(int i = 0; i < B_columns; i++)
		free(b[i]);
	free(b);
	for(int i = 0; i < A_raws; i++)
		free(A[i]);
	free(A);
	for(int i = 0; i < B_raws; i++)
		free(B[i]);
	free(B);

	return 0;
}
