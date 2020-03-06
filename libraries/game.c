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
    grids stateGrid;
    //hard codded grid
    grids checkGrid = {{
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 1, 0, 0, 0, 0, 0},
                               {0, 0, 0, 1, 0, 0, 0, 0, 0},
                               {0, 0, 0, 1, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0}}};

    //setup
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            stateGrid.grid[i][j] = 0;
        }
    }

    //game
    do {
        win = checkWin(stateGrid, checkGrid);
    } while (win == false);

}

bool checkWin(grids stateGrid, grids checkGrid) {
    bool win = true;

    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            if (checkGrid.grid[i][j] == 1 && stateGrid.grid[i][j] != 1) {
                win = false;
            }
        }
    }

    return win;
}
