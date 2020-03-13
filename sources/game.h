//
// Created by kenan.augsburger on 06.03.2020.
//

#ifndef BATTLESHIPS_GAME_H
#define BATTLESHIPS_GAME_H

#define MAX_NICKNAME_LENGTH 16

#define MAX_X 9
#define MAX_Y 9
#define OFFSET 1
#define UNCHECKED 0
#define MISS 1
#define HIT 2
#define CHECKING 3

typedef struct {
    int grid[MAX_X][MAX_Y];
} grids;

typedef struct {
    int x;
    int y;
    int direction;
} boats;

typedef struct {
    boats navy[5];
    int numberOfBoats;
} armada;

void gameHub(users currentUser);

grids fire(grids stateGrid);

grids checkState(grids stateGrid, grids checkGrid);

void displayGrid(grids stateGrid);

bool checkWin(grids stateGrid, grids checkGrid);

void displayResult(users currentUser, int tries);

scores missCount(grids currentGrid);

#endif //BATTLESHIPS_GAME_H
