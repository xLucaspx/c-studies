#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n) {
	if (n < 0) {
		printf("Invallid argument!");
		exit(1);
	}

	if (n == 0) return 0;
	if (n == 1) return 1;

	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
	int start = 0;
	int end = 20;

	printf("Fibonacci from %d to %d\n\n", start, end);

	for (int i = start; i <= end; i++) {
		printf("%d ", fibonacci(i));
	}

	printf("\n\nend\n");
	return 0;
}

