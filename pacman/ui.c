#include <stdio.h>
#include "map.h"

char wallGraph[4][7] = {
		{"......"},
		{"......"},
		{"......"},
		{"......"}
};

char ghostGraph[4][7] = {
		{" .-.  "},
		{"| OO| "},
		{"|   | "},
		{"'^^^' "}
};

char playerGraph[4][7] = {
		{" .--. "},
		{"/ _.-'"},
		{"\\  '-."},
		{" '--' "}
};

char pointGraph[4][7] = {
		{"      "},
		{" .--. "},
		{" '__' "},
		{"      "}
};

char powerGraph[4][7] = {
		{"      "},
		{" /**\\ "},
		{" \\**/ "},
		{"      "}
};

char emptyGraph[4][7] = {
		{"      "},
		{"      "},
		{"      "},
		{"      "}
};

void printGraph(char graph[4][7], int line) {
	printf("%s", graph[line]);
}

void printMap(MAP *map) {
	for (int i = 0; i < map->lineCount; i++) {
		for (int part = 0; part < 4; part++) {
			for (int j = 0; j < map->columnCount; j++) {
				switch (map->matrix[i][j]) {
					case VERTICAL_WALL:
					case HORIZONTAL_WALL:
						printGraph(wallGraph, part);
						break;
					case POINT:
						printGraph(pointGraph, part);
						break;
					case POWER:
						printGraph(powerGraph, part);
						break;
					case EMPTY:
						printGraph(emptyGraph, part);
						break;
					case PLAYER:
						printGraph(playerGraph, part);
						break;
					case ENEMY:
						printGraph(ghostGraph, part);
						break;
				}
			}
			printf("\n");
		}
	}
	printf("\n");
}
