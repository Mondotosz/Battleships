//
// Created by kenan.augsburger on 06.03.2020.
//

#include "game.h"
#include "authentication.h"

/**
 * main game function
 */
void gameHub(users currentUser) {
    bool win = false;
    int stateGrid[MAX_X][MAX_Y];
    //hard codded grid
    int checkGrid[MAX_X][MAX_Y] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    //setup
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            stateGrid[i][j] = 0;
        }
    }

    //game
    do{

    }while (win==false);

}

bool checkWin(int stateGrid[MAX_X][MAX_Y], int checkGrid[MAX_X][MAX_Y]) {
    bool win = true;

    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            if (checkGrid[i][j] == 1 && stateGrid[i][j] != 1) {
                win = false;
            }
        }
    }

    return win;
}
