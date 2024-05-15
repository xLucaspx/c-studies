#include <stdio.h>

// the asterisk in the function declaration is for receiving the memory address as parameter. That's a pointer
void incrementRef(int* n) {
	// the asterisk in the poiter is for accessing it's content in the memory
	printf("incrementRef %d %d\n", (*n), n);
	(*n)++;
	printf("incrementRef %d %d\n", (*n), n);
}

void incrementCp(int n) {
	printf("incrementCp %d %d\n", n, &n);
	n++;
	printf("incrementCp %d %d\n", n, &n);
}

int main() {
	printf("Copy\n\n");

	int i = 0;
	
	printf("main %d %d\n", i, &i);	
	incrementCp(i);
	printf("main %d %d\n", i, &i);	

	printf("\n\nReference\n\n");

	// the character `&` is for accessing the variable's memory address
	printf("main %d %d\n", i, &i);	
	incrementRef(&i);
	printf("main %d %d\n", i, &i);	

	return 0;
}

