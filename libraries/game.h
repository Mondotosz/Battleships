//
// Created by kenan.augsburger on 06.03.2020.
//

#ifndef BATTLESHIPS_GAME_H
#define BATTLESHIPS_GAME_H

#define bool	_Bool
#define true	1
#define false	0

#define MAX_NICKNAME_LENGTH 16

typedef struct{
    char nickname[MAX_NICKNAME_LENGTH];
    bool authenticated;
}users;

#define MAX_X 9
#define MAX_Y 9

typedef struct {
    int grid[MAX_X][MAX_Y];
}grids;

void gameHub(users currentUser);

bool checkWin(int stateGrid[MAX_X][MAX_Y], int checkGrid[MAX_X][MAX_Y]);

#endif //BATTLESHIPS_GAME_H
