#include<stdio.h>

int power(int base, int exponent) {
	int result = base;

	// starting in 2 cause when the exponent is 0 the result is 1 and when the exponent is 1 the result is the base
	for (int i = 2; i <= exponent; i++) {
		result *= base;
	}

	return result;
}

int main() {
	int base;
	int exponent;

	printf("Type the base: ");
	scanf("%d", &base);

	printf("Type the exponent: ");
	scanf("%d", &exponent);

	int result = power(base, exponent);

	printf("\n%d^%d = %d", base, exponent, result);
}

