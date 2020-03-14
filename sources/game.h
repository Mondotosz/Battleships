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

#define BOATS_JSON "boats.json"
#define MAX_BOAT_NAME_LENGTH 16
#define MAX_BOATS 5
#define HORIZONTAL 'H'
#define VERTICAL 'V'
#define BOAT_LENGTH 'L'
#define BOAT_DIRECTION 'D'
#define BOAT_X 'X'
#define BOAT_Y 'Y'
#define BOAT_EXISTS 'E'

typedef struct {
    int grid[MAX_X][MAX_Y];
} grids;

typedef struct {
    char name[MAX_BOAT_NAME_LENGTH];
    int length;
    int x;
    int y;
    int direction;
    bool exists;
} boat;

typedef struct {
    boat boats[MAX_BOATS];
    int numberOfBoats;
} armada;

void gameHub(users currentUser);

grids fire(grids stateGrid);

grids checkState(grids stateGrid, grids checkGrid);

void displayGrid(grids stateGrid);

bool checkWin(grids stateGrid, grids checkGrid);

void displayResult(users currentUser, int tries);

scores missCount(grids currentGrid);

armada getArmada();

armada getRandomFleet();

grids armadaToGrid(armada chosenArmada);

#endif //BATTLESHIPS_GAME_H
