#include <stdio.h>
#include <stdlib.h>

int main(void) {
	// malloc is used for memory allocation
	// sizeof is a magic function from tha language that returns the size of a given type
	// regardless of the architecture or system being used
	int *x = malloc(sizeof(int));
	*x = 10;

	printf("allocated integer: %d\n", *x);

	// when using malloc we must always "clear" with free()
	free(x);

	// example in a matrix; because it's a pointer to pointers, we use two asterisks
	// for a 5 x 10 matrix, for example, we multiply the size of each row by the number of rows
	// then we loop through each row and multiply the size of each column by the number of columns
	int **m = malloc(sizeof(int *) * 5);
	for (int i = 0; i < 5; i++) {
		m[i] = malloc(sizeof(int) * 10);
	}

	m[0][0] = 21;
	m[4][9] = 42;

	printf("allocated integers in matrix: %d %d\n", m[0][0], m[4][9]);

	// for freeing the memory, we loop through each line and clear it
	// then whe free the matrix
	for (int i = 0; i < 5; i++) {
		free(m[i]);
	}
	free(m);

	return 0;
}

