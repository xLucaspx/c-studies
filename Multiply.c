#include<stdio.h>

int main() {
	int x;
	int y;

	printf("Type the first number: ");
	scanf("%d", &x);

	printf("Type the second number: ");
	scanf("%d", &y);

	int result = x * y;

	printf("The result of %d * %d = %d\n", x, y, result);
}

