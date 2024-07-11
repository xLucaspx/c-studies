#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "pacman.h"
#include "ui.h"

MAP map;
POSITION playerPosition;
int points = 0;
int powers = 0;
char gameOverMessage[8 + 1];

void movePlayer(char direction) {
	POSITION actual = {playerPosition.x, playerPosition.y};
	POSITION next = {playerPosition.x, playerPosition.y};

	switch (direction) {
		case UP_KEY:
			next.x--;
			break;
		case DOWN_KEY:
			next.x++;
			break;
		case LEFT_KEY:
			next.y--;
			break;
		case RIGHT_KEY:
			next.y++;
			break;
		default: // else -> do nothing
			return;
	}

	// validating movement
	if (!isValidPosition(&map, next)) {
		return;
	}

	if (isPoint(&map, next)) {
		points++;
	}

	if (isPower(&map, next)) {
		points++;
		powers++;
	}

	// updating map
	moveInMap(&map, actual, next, ' ');

	// updating player position
	playerPosition.x = next.x;
	playerPosition.y = next.y;
}

void moveGhost() {
	MAP mapCopy;
	copyMap(&mapCopy, &map);

	for (int i = 0; i < mapCopy.lineCount; i++) {
		for (int j = 0; j < mapCopy.columnCount; j++) {
			if (mapCopy.matrix[i][j] == ENEMY) {
				POSITION actual = {i, j};
				POSITION next;

				chooseGhostDirection(actual, &next);

				char replacement = mapCopy.matrix[next.x][next.y];

				// avoids duplicating enemies
				if (replacement == ENEMY) {
					continue;
				}

				if (replacement == PLAYER) {
					replacement = ' ';
				}

				moveInMap(&map, actual, next, replacement);
			}
		}
	}

	freeMap(&mapCopy);
}

void chooseGhostDirection(POSITION actual, POSITION *next) {
	int options[4][2] = {
			{actual.x - 1, actual.y}, // UP
			{actual.x + 1, actual.y}, // DOWN
			{actual.x,     actual.y - 1}, // LEFT
			{actual.x,     actual.y + 1} // RIGHT
	};

	// choosing random valid direction
	srand(time(0));
	int valid = 0;

	do {
		int random = rand() % 4;
		int nextX = options[random][0];
		int nextY = options[random][1];

		if (isValidPosition(&map, (POSITION) {nextX, nextY})) {
			next->x = nextX;
			next->y = nextY;
			valid = 1;
		}
	} while (!valid);
}

void explodeBomb(POSITION position, int sumX, int sumY, int times) {
	if (times == 0) return;

	int newX = position.x + sumX;
	int newY = position.y + sumY;
	POSITION new = {newX, newY};

	// doesn't explode through walls
	if (isWall(&map, new)) return;

	// only affects enemies
	if (isEnemy(&map, new)) {
		// removes enemy from map
		map.matrix[newX][newY] = EMPTY;
		points += 5; // kill enemy = 5 points
	}
	// recursive call
	explodeBomb(new, sumX, sumY, times - 1);
}

void usePower() {
	if (!powers) return;

	// explodes bomb 2 positions to each direction
	explodeBomb(playerPosition, -1, 0, 2);
	explodeBomb(playerPosition, 1, 0, 2);
	explodeBomb(playerPosition, 0, -1, 2);
	explodeBomb(playerPosition, 0, 1, 2);

	powers--;
}

int gameOver() {
	return victory() || defeat();
}

int victory() {
	int enemiesDied = !findInMap(ENEMY, &map, &(POSITION) {});
	int noMorePoints = !(findInMap(POINT, &map, &(POSITION) {}) || findInMap(POWER, &map, &(POSITION) {}));
	int win = 0;

	if (noMorePoints) {
		if (enemiesDied) {
			points += 45; // bonus 100%
			sprintf(gameOverMessage, "You win!");
			return 1;
		}
		if (powers == 0) {
			points += 20; // enemies alive but no more powers
			sprintf(gameOverMessage, "You win!");
			return 1;
		}
	}

	// killed all enemies but didn't get all the points
	if (enemiesDied) {
		sprintf(gameOverMessage, "You win!");
		return 1;
	}

	return 0;
}

int defeat() {
	int lost = 0;

	// Player died
	if (!findInMap(PLAYER, &map, &(POSITION) {})) {
		lost = 1;
		sprintf(gameOverMessage, "You lost");
	}

	return lost;
}

int main() {
	readMap(&map);
	findInMap(PLAYER, &map, &playerPosition);

	do {
		printf("\e[1;1H\e[2J"); // clear screen
		printMap(&map);
		printf("Points: %d | Bombs: %d\n", points, powers);

		char command;
		scanf(" %c", &command);
		command = tolower(command);

		if (command == POWER_KEY) {
			usePower();
		} else {
			movePlayer(command);
		}

		moveGhost();

	} while (!gameOver());

	printf("\e[1;1H\e[2J"); // clear screen
	printMap(&map);
	printf("Points: %d\n", points);
	printf("\n%s\n", gameOverMessage);

	freeMap(&map);

	printf("\nGame over\n");

	return 0;
}
