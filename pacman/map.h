#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H

#define PLAYER '@'
#define ENEMY '#'
#define POINT '.'
#define POWER '*'
#define EMPTY ' '
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'

struct map {
	// two asterisks because it will be a pointer of pointers (matrix)
	char **matrix;
	int lineCount;
	int columnCount;
};

typedef struct map MAP;

struct position {
	int x;
	int y;
};

typedef struct position POSITION;

int findInMap(char needle, MAP *haystack, POSITION *position);

int isEnemy(MAP *map, POSITION position);

int isPoint(MAP *map, POSITION position);

int isPower(MAP *map, POSITION position);

int isWall(MAP *map, POSITION position);

int isValidPosition(MAP *map, POSITION position);

void allocateMap(MAP *map);

void copyMap(MAP *copy, MAP *map);

void freeMap(MAP *map);

void moveInMap(MAP *map, POSITION actual, POSITION next, char replacement);

void readMap(MAP *map);

#endif // PACMAN_MAP_H
