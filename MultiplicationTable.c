#include<stdio.h>

int main() {
	int n;
	
	printf("Type a number: ");
	scanf("%d", &n);

	for (int i = 1; i <= 10; i++) {
		printf("%d x %d = %d\n", n, i, n * i);
	}

	printf("\nend\n");
}

