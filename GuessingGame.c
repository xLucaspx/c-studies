#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// tudo o que começa com # é chamado de diretiva; define é utilizado para declarar uma constante:
#define EASY_TRIES 15
#define MEDIUM_TRIES 10
#define HARD_TRIES 5

int main(void) {
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
    printf("\n");

    printf("[1] Easy (%d tries)\n", EASY_TRIES);
    printf("[2] Medium (%d tries)\n", MEDIUM_TRIES);
    printf("[3] Hard (%d tries)\n", HARD_TRIES);

    int option;
    int tries;
    printf("Choose... ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            tries = EASY_TRIES;
            break;
        case 2:
            tries = MEDIUM_TRIES;
            break;
        case 3:
            tries = HARD_TRIES;
            break;
            // hidden bonus
        case 42:
            tries = 42;
            break;
        default:
            tries = 0;
    }

    long seed = time(0); // EPOCH
    srand(seed); // seeding rand with seconds since 1970
    int secretNumber = rand() % 100;

    int playerGuess = 0;
    float points = 1000.0f;

    for (int i = 0; i < tries; i++) {
//        if (playerGuess == secretNumber) continue;

        printf("\nTries: %d of %d\n", i + 1, tries);

        printf("What's your guess? ");
        scanf("%d", &playerGuess);

        if (playerGuess < 0) {
            printf("Only positive numbers are allowed!\n");
            i--;
            continue;
        }

        if (playerGuess == secretNumber) {
            printf("\nCongrats, you nailed it in %d tries!\n", tries);
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
                printf("\nThe secret number was %d\n", secretNumber);
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
