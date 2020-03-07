//
// Created by kenan.augsburger on 06.03.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utilities/utilities.h"
#include "authentication.h"
#include "game.h"

/**
 * main game function
 */
void gameHub(users currentUser) {
    bool win = false;
    grids stateGrid;
    //hard codded grid
    grids checkGrid = {{
                               {1, 1, 1, 1, 1, 1, 1, 1, 1},
                               {1, 1, 1, 1, 1, 1, 1, 1, 1},
                               {1, 1, 2, 1, 1, 1, 1, 1, 1},
                               {1, 1, 2, 1, 1, 1, 1, 1, 1},
                               {1, 1, 2, 1, 1, 1, 1, 1, 1},
                               {1, 1, 1, 1, 1, 1, 1, 1, 1},
                               {1, 1, 1, 1, 1, 1, 1, 1, 1},
                               {1, 1, 1, 1, 1, 1, 1, 1, 1},
                               {1, 1, 1, 1, 1, 1, 1, 1, 1}}};

    //setup
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            stateGrid.grid[i][j] = UNCHECKED;
        }
    }

    //game
    do {
        //displays the grid before firing
        displayGrid(stateGrid);
        //select the shooting coordinates
        stateGrid = fire(stateGrid);
        //compare the 2 grids
        stateGrid = checkState(stateGrid, checkGrid);
        //check if it's a win
        win = checkWin(stateGrid, checkGrid);
    } while (win == false);

}

void displayGrid(grids displayedGrid) {
    system("cls");

    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            switch (displayedGrid.grid[i][j]) {
                case UNCHECKED:
                    printf("%c%c", 176, 176);
                    break;
                case MISS:
                    printf("  ");
                    break;
                case HIT:
                    printf("%c%c", 219, 219);
                    break;
                default:
                    printf("Unexpected value : %d", displayedGrid.grid[i][j]);
            }
        }
        printf("\n");
    }
}

grids fire(grids stateGrid) {
    int x;
    int y;

    do {
        printf("\n");
        //asks for x coordinates
        printf("x ");
        x = getInt(OFFSET, MAX_X);
        x -= OFFSET;

        //asks for y coordinates and convert them
        printf("y ");
        y = getIntFromChar(OFFSET, MAX_Y);
        y -= OFFSET;

        if (stateGrid.grid[x][y] != UNCHECKED) {
            printf("\n");
            printf("You already checked this cell !\n");
        }

    } while (stateGrid.grid[y][x] != UNCHECKED);

    //puts them in stateGrid
    stateGrid.grid[y][x] = CHECKING;

    return stateGrid;
}

grids checkState(grids stateGrid, grids checkGrid) {
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            if (stateGrid.grid[i][j] == CHECKING) {
                stateGrid.grid[i][j] = checkGrid.grid[i][j];
            }
        }
    }
    return stateGrid;
}

bool checkWin(grids stateGrid, grids checkGrid) {
    bool win = true;

    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            if (checkGrid.grid[i][j] == HIT && stateGrid.grid[i][j] != HIT) {
                win = false;
            }
        }
    }

    return win;
}

void displayResult(users currentUser, int tries) {
    system("cls");
    if (currentUser.authenticated) {
        printf("Well done %s !\n", currentUser.nickname);
    } else {
        printf("Well done !\n");
    }

    printf("\n");
    printf("Tries : %d", tries);
    printf("\n");
    pause();
}