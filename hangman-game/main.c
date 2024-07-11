#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// in C, functions must be declared before being called; the compiler reads the file from the top
// to the bottom. We can place the functions signatures in the beginning of the file -- like global
// variables -- to tell the compiler that those functions exist in the program:
// void drawGameHeader();
// int alreadyGuessed();
// ...
// This is so common that we can place it in a header file (.h) and use
// #include. Our header files are included with double quotes
#include "hangman.h"

// global variables
char secretWord[WORD_LENGTH];
char output[WORD_LENGTH];
int secretWordLength;

char guessArr[26];
int guessCount = 0;

char errorsArr[6];
int errorsCount = 0;
int hits = 0;

void drawGameHeader() {
	printf("  _______  \n");
	printf(" |/      | \n");
	printf(" |         \n");
	printf(" |          THE HANGMAN \n");
	printf(" |             GAME     \n");
	printf(" |         \n");
	printf(" |         \n");
	printf("_|___      \n\n");
}

void chooseWord() {
// fopen returns a pointer to a file
	FILE *f = fopen("words.txt", "r");

	if (f == 0) {
		perror("Word database not available!\n\n");
		exit(1);
	}

	// the first line of words.txt must be the quantity of words in the file
	int wordCount;
	fscanf(f, "%d", &wordCount);

	// choosing a random word from the file
	srand(time(0));
	int randomNumber = rand() % wordCount;

	for (int i = 0; i <= randomNumber; i++) {
		fscanf(f, "%s", secretWord);
	}

	fclose(f);

	secretWordLength = strlen((secretWord));
	for (int i = 0; i < secretWordLength; i++) {
		output[i] = '_';
	}
}

int won() {
	return hits == secretWordLength;
//	for (int i = 0; i < secretWordLength; i++) {
//		if (!alreadyGuessed(secretWord[i])) {
//			return 0;
//		}
//	}
//
//	return 1;
}

int hanged() {
	return errorsCount >= MAX_TRIES;
}

void guess() {
	// to read a single char with scanf it's necessary to use a blank space before %c;
	// that occurs because anything can be a char, including enter. The blank space informs that
	// we want to ignore the enter and get only the letter.
	char letter;
	printf("\nWhat's your guess? ");
	scanf(" %c", &letter);

	letter = toupper(letter);

	if (alreadyGuessed(letter)) {
		printf("\nHold on, brother... you've already typed the letter %c\n\n", letter);
		return;
	}

	if (wordContains(letter)) {
		printf("\nThat's right brother, the secret word contains the letter %c\n", letter);
	} else {
		printf("\nHang in there, brother... the secret word doesn't contain the letter %c\n", letter);
		errorsArr[errorsCount] = letter;
		errorsCount++;
	}

	// updating the array of guesses and incrementing the guess count
	guessArr[guessCount] = letter;
	guessCount++;
}

int wordContains(char letter) {
	int contains = 0;

	for (int i = 0; i < secretWordLength; i++) {
		if (letter == secretWord[i]) {
			output[i] = letter;
			hits++;
			contains = 1;
		}
	}

	return contains;
}

int alreadyGuessed(char letter) {
	for (int i = 0; i < guessCount; i++) {
		if (guessArr[i] == letter) {
			return 1;
		}
	}

	return 0;
}

void drawGibbet() {
	printf("\nLives: %d of %d\n", MAX_TRIES - errorsCount, MAX_TRIES);

	printf("  _______       \n");
	printf(" |/      |      \n");
	// head -> errors >= 1
	printf(" |      %c%c%c  \n",
				 (errorsCount >= 1 ? '(' : ' '),
				 (errorsCount >= 1 ? '_' : ' '),
				 (errorsCount >= 1 ? ')' : ' '));
	// body -> errors >= 2
	// left arm -> errors >= 3
	// right arm -> errors >= 4
	printf(" |      %c%c%c  \n",
				 (errorsCount >= 3 ? '\\' : ' '),
				 (errorsCount >= 2 ? '|' : ' '),
				 (errorsCount >= 4 ? '/' : ' '));
	printf(" |       %c     \n", (errorsCount >= 2 ? '|' : ' '));
	// left leg -> errors >= 5
	// right leg -> errors >= 6
	printf(" |      %c %c   \n", (errorsCount >= 5 ? '/' : ' '), (errorsCount >= 6 ? '\\' : ' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");

	for (int i = 0; i < secretWordLength; i++) {
		printf("%c ", output[i]);
	}

	printf("\n\nWrong letters:\n");

	for (int i = 0; i < errorsCount; i++) {
		printf("%c - ", errorsArr[i]);
	}

	printf("\n");
}

void hangmanGame() {
	chooseWord();

	do {
		printf("\e[1;1H\e[2J"); // clear screen
		drawGibbet();
		guess();
	} while (!won() && !hanged());

	drawGibbet();

	if (won()) {
		printf("\nCongratulations, brother! You won!\n\n");

		printf("       ___________       \n");
		printf("      '._==_==_=_.'      \n");
		printf("      .-\\:      /-.     \n");
		printf("     | (|:.     |) |     \n");
		printf("      '-|:.     |-'      \n");
		printf("        \\::.    /       \n");
		printf("         '::. .'         \n");
		printf("           ) (           \n");
		printf("         _.' '._         \n");
		printf("        '-------'        \n\n");

	} else {
		printf("\nSorry, brother... you were hanged\n");
		printf("The secret word was ->%s<-\n\n", secretWord);

		printf("      _______________         \n");
		printf("     /               \\       \n");
		printf("    /                 \\      \n");
		printf("  //                   \\/\\  \n");
		printf("  \\|   XXXX     XXXX   | /   \n");
		printf("   |   XXXX     XXXX   |/     \n");
		printf("   |   XXX       XXX   |      \n");
		printf("   |                   |      \n");
		printf("   \\__      XXX      __/     \n");
		printf("     |\\     XXX     /|       \n");
		printf("     | |           | |        \n");
		printf("     | I I I I I I I |        \n");
		printf("     |  I I I I I I  |        \n");
		printf("     \\_             _/       \n");
		printf("       \\_         _/         \n");
		printf("         \\_______/           \n\n");
	}

	resetGame();
}

void addWord() {
	char newWord[WORD_LENGTH];

	printf("Type in the new word: ");
	scanf("%s", newWord);

	strupr(newWord);

	FILE *f = fopen("words.txt", "r+");

	if (f == 0) {
		perror("Word database not available!\n\n");
		exit(1);
	}

	// updating the word count in words.txt
	int wordCount;
	fscanf(f, "%d", &wordCount);
	wordCount++;
	// setting the pointer to the beginning of the file
	fseek(f, 0, SEEK_SET);
	// overwriting previous count
	fprintf(f, "%d", wordCount);

	// setting the pointer to the end of the file
	fseek(f, 0, SEEK_END);
	// writing new word
	fprintf(f, "%s\n", newWord);

	fclose(f);
}

void resetGame() {
	guessCount = 0;
	errorsCount = 0;
	hits = 0;
}

// The `main` function is usually the last one of the file
int main() {
	drawGameHeader();

	int run = 1;

	do {
		printf("-- MENU --\n\n");
		printf("[1] Play\n");
		printf("[2] Add word\n\n");
		printf("Choose: ");

		int option;
		scanf("%d", &option);

		switch (option) {
			case 1:
				hangmanGame();
				break;
			case 2:
				addWord();
				break;
			default:
				run = 0;
				break;
		}

	} while (run);

	printf("\nGame over\n");

	return 0;
}
