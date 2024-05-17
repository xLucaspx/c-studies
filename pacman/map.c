#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

int findInMap(char needle, MAP *haystack, POSITION *position) {
	// finds player position
	for (int i = 0; i < haystack->lineCount; i++) {
		for (int j = 0; j < haystack->columnCount; j++) {
			if (haystack->matrix[i][j] == needle) {
				position->x = i;
				position->y = j;
				return 1;
			}
		}
	}
	return 0;
}

int isWall(MAP *map, POSITION position) {
	return (map->matrix[position.x][position.y] == HORIZONTAL_WALL
					|| map->matrix[position.x][position.y] == VERTICAL_WALL);
}

int isEnemy(MAP *map, POSITION position) {
	return map->matrix[position.x][position.y] == ENEMY;
}

int isValidPosition(MAP *map, POSITION position) {
	int x = position.x;
	int y = position.y;

	// out of bounds isn't a valid position
	if (x >= map->lineCount) return 0;
	if (y >= map->columnCount) return 0;

	// floor and wall aren't valid positions
	if (isWall(map, position)) return 0;

	// enemies cannot be overwritten
	if (isEnemy(map, position)) return 0;

	return 1;
}

int isPoint(MAP *map, POSITION position) {
	return map->matrix[position.x][position.y] == POINT;
}

int isPower(MAP *map, POSITION position) {
	return map->matrix[position.x][position.y] == POWER;
}

void moveInMap(MAP *map, POSITION actual, POSITION next, char replacement) {
	// get the character in actual position
	char character = map->matrix[actual.x][actual.y];

	// replaces character with replacement
	map->matrix[actual.x][actual.y] = replacement;
	// moves character to next position
	map->matrix[next.x][next.y] = character;
}

// we're passing a pointer to a struct MAP; to access it's variables
// we can use * (E.g.: (*map).lineCount) or the shortcut -> (E.g.: map->lineCount)
void readMap(MAP *map) {
	FILE *f = fopen("map_1.txt", "r");

	if (f == 0) {
		printf("An error occurred when trying to load the map\n");
		exit(1);
	}

	// the first line of the map must contain the number of lines and columns
	fscanf(f, "%d %d", &(map->lineCount), &(map->columnCount));
	// printf("Lines: %d Columns: %d\n", mapLineCount, mapColumnCount);X

	// dynamic memory allocation
	allocateMap(map);

	// reading map from file
	for (int i = 0; i < map->lineCount; i++) {
		// passing only one dimension of the matrix equals passing the whole line
		fscanf(f, "%s", map->matrix[i]);
	}

	fclose(f);
}

void copyMap(MAP *copy, MAP *map) {
	copy->lineCount = map->lineCount;
	copy->columnCount = map->columnCount;

	allocateMap(copy);

	for (int i = 0; i < map->lineCount; i++) {
		// strcpy copies a char array until a \0 char
		strcpy(copy->matrix[i], map->matrix[i]);
	}
}

void allocateMap(MAP *map) {
	// size of a pointer of char (each line of the matrix is an array: a pointer)
	map->matrix = malloc(sizeof(char *) * map->lineCount);
	for (int i = 0; i < map->lineCount; i++) {
		// +1 because it needs to end with \0
		map->matrix[i] = malloc(sizeof(char) * (map->columnCount + 1));
	}
}

void freeMap(MAP *map) {
	for (int i = 0; i < map->lineCount; ++i) {
		free(map->matrix[i]);
	}
	free(map->matrix);
}
