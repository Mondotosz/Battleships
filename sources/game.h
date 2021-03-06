//
// Created by kenan.augsburger on 06.03.2020.
//

#ifndef BATTLESHIPS_GAME_H
#define BATTLESHIPS_GAME_H

#define MAX_NICKNAME_LENGTH 16

#define MAX_X 26
#define MAX_Y 26
#define OFFSET 1
#define UNCHECKED 0
#define MISS 1
#define HIT 2
#define CHECKING 3

#define MAX_BOAT_NAME_LENGTH 16
#define MAX_BOATS 5
#define HORIZONTAL 'H'
#define VERTICAL 'V'

typedef struct {
    int grid[MAX_Y][MAX_X];
    int maxX;
    int maxY;
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
    int maxX;
    int maxY;
} armada;


typedef struct {
    char name[MAX_NICKNAME_LENGTH];
    char author[MAX_NICKNAME_LENGTH];
    grids content;
} map;

#define MAP_LIST_FILE "maps.list"
#define MAP_FOLDER "maps/"
#define MAP_EXTENSION ".map"
#define MAX_MAPS 50

typedef struct {
    map maps[MAX_MAPS];
    int range;
} mapList;

void gameHub(users currentUser);

void game(users player, grids checkGrid);

grids fire(grids map);

grids checkState(grids stateGrid, grids checkGrid);

void displayGrid(grids stateGrid);

bool checkWin(grids stateGrid, grids checkGrid);

void displayResult(users player, scores score);

scores missCount(grids map);

armada getRandomFleet(grids grid);

grids armadaToGrid(armada chosenArmada, grids map);

grids getMap(char *mapName);

mapList getMapList();

void displayMapList(mapList list);

void saveMap(map newMap);

map createMap(users player);

bool checkOverlap(armada fleet, boat newBoat);

#endif //BATTLESHIPS_GAME_H
