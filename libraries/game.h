//
// Created by kenan.augsburger on 06.03.2020.
//

#ifndef BATTLESHIPS_GAME_H
#define BATTLESHIPS_GAME_H

#define MAX_NICKNAME_LENGTH 16

#define MAX_X 9
#define MAX_Y 9
#define UNCHECKED 0
#define HIT 1
#define MISS 2
#define CHECKING 3

typedef struct {
    int grid[MAX_X][MAX_Y];
} grids;

void gameHub(users currentUser);

grids fire(grids stateGrid);

grids checkState(grids stateGrid, grids checkGrid);

bool checkWin(grids stateGrid, grids checkGrid);

#endif //BATTLESHIPS_GAME_H
