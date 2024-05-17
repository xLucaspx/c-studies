#ifndef PACMAN_H
#define PACMAN_H

#include "map.h"

#define UP_KEY 'w'
#define LEFT_KEY 'a'
#define DOWN_KEY 's'
#define RIGHT_KEY 'd'
#define POWER_KEY 'f'

int gameOver();

int victory();

int defeat();

void moveGhost();

void chooseGhostDirection(POSITION actual, POSITION *next);

void movePlayer(char direction);

void usePower();

void explodeBomb(POSITION position, int sumX, int sumY, int times);

#endif // PACMAN_H
