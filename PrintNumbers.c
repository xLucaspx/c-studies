#include<stdio.h>

#define BEGIN 1
#define END 100

int main() {
	printf("Numbers from %d to %d\n\n", BEGIN, END);

	for (int i = 1; i <= 100; i++) {
		printf("%d ", i);
	}

	printf("\n\nend\n");
}

