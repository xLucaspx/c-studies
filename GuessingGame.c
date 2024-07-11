#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// tudo o que começa com # é chamado de diretiva; define é utilizado para declarar uma constante:
#define EASY 1
#define EASY_TRIES 15
#define MEDIUM 2
#define MEDIUM_TRIES 10
#define HARD 3
#define HARD_TRIES 5

int main() {
	printf("\n\n");
	printf("###################################################################################\n");
	printf("############            ##   ######   ##            ##            ##            ###\n");
	printf("###########            ##   ######   ##            ##            ##            ####\n");
	printf("##########   ###########   ######   ##   ###########   ###########   ##############\n");
	printf("#########   ###########   ######   ##   ###########   ###########   ###############\n");
	printf("########   ###      ##   ######   ##        ######            ##            #######\n");
	printf("#######   ###      ##   ######   ##        ######            ##            ########\n");
	printf("######   ######   ##   ######   ##   ####################   ###########   #########\n");
	printf("#####   ######   ##   ######   ##   ####################   ###########   ##########\n");
	printf("####            ##            ##            ##            ##            ###########\n");
	printf("###            ##            ##            ##            ##            ############\n");
	printf("###################################################################################\n");
	printf("Guess the secret number between 1 and 99!\n\n");

	printf("[%d] Easy (%d tries)\n", EASY, EASY_TRIES);
	printf("[%d] Medium (%d tries)\n", MEDIUM, MEDIUM_TRIES);
	printf("[%d] Hard (%d tries)\n", HARD, HARD_TRIES);
	printf("Choose... ");

	int option;
	int tries;
	scanf("%d", &option);

	switch (option) {
		case EASY:
			tries = EASY_TRIES;
			break;
		case MEDIUM:
			tries = MEDIUM_TRIES;
			break;
		case HARD:
			tries = HARD_TRIES;
			break;
		case 42: // hidden bonus
			tries = 42;
			break;
		default:
			printf("\nInvalid option!");
			tries = 0;
	}

	long seed = time(0); // EPOCH
	srand(seed); // seeding rand with seconds since 1970
	int secretNumber = rand() % 100;

	int playerGuess = 0;
	float points = 1000.0f;

	for (int i = 0; i < tries; i++) {
		// if (playerGuess == secretNumber) continue;

		printf("\nTries: %d of %d\n", i + 1, tries);

		printf("What's your guess? ");
		scanf("%d", &playerGuess);

		if (playerGuess < 0) {
			printf("Only positive numbers are allowed!\n");
			i--;
			continue;
		}

		if (playerGuess == secretNumber) {
			printf("\nCongrats, you nailed it in %d tries!\n", i + 1);
			printf("Score: %.1f points", points);
			break;
		} else {
			printf("That's not right, brother... the number is ");

			if (secretNumber < playerGuess) {
				printf("smaller ");
			} else {
				printf("greater ");
			}

			printf("than %d\n", playerGuess);

			float lostPoints = (float) abs(playerGuess - secretNumber) / 2.0f;
			points = points - lostPoints;

			if (i == tries - 1) {
				printf("\nYou lost...\nThe secret number was %d\n", secretNumber);
				printf("Score: %.1f points\n", points);
			}
		}
	}
// infinite tries:
//    while (playerGuess != secretNumber) {
//        printf("\nTries: %d\n", tries);
////        printf("Points: %.1f\n", points);42
//
//        printf("What's your guess? ");
//        scanf("%d", &playerGuess);
//
//        if (playerGuess < 0) {
//            printf("Only positive numbers are allowed!\n");
//            continue;
//        }
//
//        if (playerGuess == secretNumber) {
//            printf("Congrats, you nailed it in %d tries!\n", tries);
//            printf("Score: %.1f points", points);
//            continue;
//        }
//
//        printf("That's not right, brother... the number is ");
//
//        if (secretNumber < playerGuess) {
//            printf("smaller ");
//        } else {
//            printf("greater ");
//        }
//
//        printf("than %d\n", playerGuess);
//
//        float lostPoints = (float) abs(playerGuess - secretNumber) / 2.0f;
//        points = points - lostPoints;
//
//        tries++;
//    }

	printf("\nGame over!\n");
	return 0;
}
