#include<stdio.h>

#define BEGIN 1
#define END 100

int main() {
        printf("Sum numbers from %d to %d\n\n", BEGIN, END);
		
	int sum = 0;

        for (int i = 1; i <= 100; i++) {
                sum += i;
        }

        printf("sum = %d\n\nend\n", sum);
}

