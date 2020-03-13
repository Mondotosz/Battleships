//
// Created by kenan.augsburger on 06.03.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities/utilities.h"
#include "score.h"
#include "authentication.h"
#include "game.h"

/**
 * main game function
 */
void gameHub(users currentUser) {
    bool win = false;
    scores currentScore;
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

    currentScore.tries = 0;

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
        printf("tries : %d\n", currentScore.tries);
        //select the shooting coordinates
        stateGrid = fire(stateGrid);
        currentScore.tries++;
        //compare the 2 grids
        stateGrid = checkState(stateGrid, checkGrid);
        //check if it's a win
        win = checkWin(stateGrid, checkGrid);
    } while (win == false);

    displayResult(currentUser, currentScore.tries);

    if (currentUser.authenticated) {
        strcpy(currentScore.nickname, currentUser.nickname);
        newScore(currentScore);
    }

    //TODO:enhance result functions

}

/**
 * Displays the grid with formatting
 * @param displayedGrid
 */
void displayGrid(grids displayedGrid) {
    int yOffsetValue = 2;
    int xOffsetValue = 2 * yOffsetValue;

    system("cls");

    offsetY(yOffsetValue);

    //grid top
    offsetX(xOffsetValue);
    printf("%c", 201);
    for (int m = 0; m < MAX_X * 3 + 2; ++m) {
        if ((m + 1) % 3 == 0) {
            printf("%c", 203);
        } else {
            printf("%c", 205);
        }
    }
    printf("%c\n", 187);

    //integer markers
    offsetX(xOffsetValue);
    printf("%c  %c", 186, 186);
    for (int l = 1; l < 10; ++l) {
        printf("%d %c", l, 186);
    }
    printf("\n");
    for (int i = 0; i < MAX_X; ++i) {

        //vertical gap
        offsetX(xOffsetValue);
        printf("%c", 204);
        for (int k = 0; k < MAX_X * 3 + 2; ++k) {
            if ((k + 1) % 3 == 0) {
                printf("%c", 206);
            } else {
                printf("%c", 205);
            }
        }
        printf("%c\n", 185);

        //side letter indicators
        offsetX(xOffsetValue);
        printf("%c%c %c", 186, intToChar(i + 1), 186);

        for (int j = 0; j < MAX_Y; ++j) {
            switch (displayedGrid.grid[i][j]) {
                case UNCHECKED:
                    printf("%c%c%c", 176, 176, 186);
                    break;
                case MISS:
                    printf("  %c", 186);
                    break;
                case HIT:
                    printf("%c%c%c", 219, 219, 186);
                    break;
                default:
                    printf("\nUnexpected value : %d\n", displayedGrid.grid[i][j]);
            }
        }
        printf("\n");
    }

    //grid bottom
    offsetX(xOffsetValue);
    printf("%c", 200);
    for (int m = 0; m < MAX_X * 3 + 2; ++m) {
        if ((m + 1) % 3 == 0) {
            printf("%c", 202);
        } else {
            printf("%c", 205);
        }
    }
    printf("%c\n", 188);

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