#include<stdio.h>

int main() {
	// declaring an char array
	char word[20];
	// in C, an array is a pointer; it points to the memory address of the first position:
	printf("%d %d\n\n", word, &word[0]);
	// the elements are stored side by side in the memory based on their size; e.g.: an integer occupies 4 bytes, so if we have an integer array that's stored in the position 10 of the memory, the fist element (0) will be at the position 10 (10 + 0 * 4), the second (1) in the position 14 (10 + 1 * 4), the third (2) in the position 18 (10 + 2 * 4) and so on

	// we can use `sprintf` to store a string inside the array:
	sprintf(word, "LOREM IPSUM");

	// in a char array we can store any characters; when using `%s`, for the language
	// to know that the string is over, the character used is `\0`
	
	/*
	 word[0] = 'L';
	 word[1] = 'O';
	 ...
	 word[10] = 'M';
	 word[11] = '\0';
	 */

	printf("%s\n", word);


	return 0;
}

