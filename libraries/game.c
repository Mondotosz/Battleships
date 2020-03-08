//
// Created by kenan.augsburger on 06.03.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "utilities/utilities.h"
#include "authentication.h"
#include "game.h"

/**
 * main game function
 */
void gameHub(users currentUser) {
    bool win = false;
    int tries = 0;
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
        printf("\n");
        printf("tries : %d\n", tries);
        //select the shooting coordinates
        stateGrid = fire(stateGrid);
        tries++;
        //compare the 2 grids
        stateGrid = checkState(stateGrid, checkGrid);
        //check if it's a win
        win = checkWin(stateGrid, checkGrid);
    } while (win == false);

    displayResult(currentUser, tries);

}

void displayGrid(grids displayedGrid) {
    system("cls");

    printf("  1  2  3  4  5  6  7  8  9\n");
    for (int i = 0; i < MAX_X; ++i) {
        printf("%c ", intToChar(i + 1));
        for (int j = 0; j < MAX_Y; ++j) {
            switch (displayedGrid.grid[i][j]) {
                case UNCHECKED:
                    printf("%c%c ", 176, 176);
                    break;
                case MISS:
                    printf("   ");
                    break;
                case HIT:
                    printf("%c%c ", 219, 219);
                    break;
                default:
                    printf("\nUnexpected value : %d\n", displayedGrid.grid[i][j]);
            }
        }
        printf("\n");
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

        if (stateGrid.grid[y][x] != UNCHECKED) {
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