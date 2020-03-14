//
// Created by kenan.augsburger on 06.03.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utilities/utilities.h"
#include "score.h"
#include "authentication.h"
#include "game.h"

//TODO:define grid with boats

/**
 * main game function
 */
void gameHub(users currentUser) {
    bool win = false;
    scores currentScore;
    grids stateGrid;
    grids checkGrid;
    armada fleet;

    //setup
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            stateGrid.grid[i][j] = UNCHECKED;
        }
    }

    //gets the standardized armada structure
    //fleet = getArmada();
    fleet = getRandomFleet();
    //translates its boats to grid coordinates
    checkGrid = armadaToGrid(fleet);
    //defaults miss count to 0
    currentScore.misses = 0;

    //game
    do {
        //displays the grid before firing
        displayGrid(checkGrid);
        offsetY(2);
        offsetX(4);
        printf("misses : %d\n", currentScore.misses);
        //select the shooting coordinates
        stateGrid = fire(stateGrid);
        currentScore = missCount(stateGrid);
        //compare the 2 grids
        stateGrid = checkState(stateGrid, checkGrid);
        //check if it's a win
        win = checkWin(stateGrid, checkGrid);
    } while (win == false);

    displayResult(currentUser, currentScore.misses);

    system("cls");
    if (!currentUser.authenticated) {
        printf("\n");
        printf("Would you like to save your score ?");
        if (trueFalse()) {
            currentUser = authenticateUser(currentUser);
        }
    }

    if (currentUser.authenticated) {
        strcpy(currentScore.nickname, currentUser.nickname);
        newScore(currentScore);
    }

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
    for (int m = 0; m < MAX_Y * 3 + 2; ++m) {
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
    for (int l = 1; l < MAX_Y + 1; ++l) {
        printf("%2d%c", l, 186);
    }
    printf("\n");
    for (int i = 0; i < MAX_X; ++i) {

        //vertical gap
        offsetX(xOffsetValue);
        printf("%c", 204);
        for (int k = 0; k < MAX_Y * 3 + 2; ++k) {
            if ((k + 1) % 3 == 0) {
                printf("%c", 206);
            } else {
                printf("%c", 205);
            }
        }
        printf("%c\n", 185);

        //side letter indicators
        offsetX(xOffsetValue);
        printf("%c %c%c", 186, intToChar(i + 1), 186);

        //displays cell state
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
                    printf("\nUnexpected value : %d\n", displayedGrid.grid[i][j]);
            }
            printf("%c", 186);
        }
        printf("\n");
    }

    //grid bottom
    offsetX(xOffsetValue);
    printf("%c", 200);
    for (int m = 0; m < MAX_Y * 3 + 2; ++m) {
        if ((m + 1) % 3 == 0) {
            printf("%c", 202);
        } else {
            printf("%c", 205);
        }
    }
    printf("%c\n", 188);

}

//TODO:fire takes both values at once

grids fire(grids stateGrid) {
    int x;
    int y;

    do {
        printf("\n");
        //asks for x coordinates
        offsetX(4);
        printf("x ");
        x = getInt(OFFSET, MAX_X);
        x -= OFFSET;

        //asks for y coordinates and convert them
        offsetX(4);
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

void displayResult(users currentUser, int misses) {
    system("cls");
    if (currentUser.authenticated) {
        printf("Well done %s !\n", currentUser.nickname);
    } else {
        printf("Well done !\n");
    }

    printf("\n");
    printf("misses : %d", misses);
    printf("\n");
    pause();
}

scores missCount(grids currentGrid) {
    scores currentScore;
    currentScore.misses = 0;

    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            if (currentGrid.grid[i][j] == MISS) {
                currentScore.misses++;
            }
        }

    }

    return currentScore;
}


armada getRandomFleet() {
    armada fleet = {
            {
                    {"Destroyer", 2, 0, 0, HORIZONTAL, false},
                    {"Submarine", 3, 0, 0, HORIZONTAL, false},
                    {"Cruiser", 3, 0, 0, HORIZONTAL, false},
                    {"Battleship", 4, 0, 0, HORIZONTAL, false},
                    {"Carrier", 5, 0, 0, HORIZONTAL, false}
            },
            MAX_BOATS
    };
    bool overlap;

    //TODO:avoid overlap

    //initialize a random seed
    srand((unsigned) time(NULL));

    for (int i = 0; i < fleet.numberOfBoats; ++i) {

        //randomize the direction
        if (rand() % 2 == 0) {
            fleet.boats[i].direction = VERTICAL;
            fleet.boats[i].y = rand() % (MAX_X - fleet.boats[i].length + 1);
            fleet.boats[i].x = rand() % MAX_Y;
            fleet.boats[i].exists = true;
        } else {
            fleet.boats[i].direction = HORIZONTAL;
            fleet.boats[i].x = rand() % (MAX_Y - fleet.boats[i].length + 1);
            fleet.boats[i].y = rand() % MAX_X;
            fleet.boats[i].exists = true;
        }

    }

    return fleet;
}

grids armadaToGrid(armada chosenArmada) {
    grids translatedGrid;

    //defaults every values to MISS
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            translatedGrid.grid[i][j] = MISS;
        }
    }


    for (int i = 0; i < chosenArmada.numberOfBoats; ++i) {

        //only adds existing boats
        if (chosenArmada.boats[i].exists) {

            //places them according to direction
            switch (chosenArmada.boats[i].direction) {
                case HORIZONTAL:

                    //repeats for the length of the boat
                    for (int j = 0; j < chosenArmada.boats[i].length; ++j) {
                        translatedGrid.grid[chosenArmada.boats[i].y][chosenArmada.boats[i].x + j] = HIT;
                    }

                    break;
                case VERTICAL:

                    //repeats for the length of the boat
                    for (int j = 0; j < chosenArmada.boats[i].length; ++j) {
                        translatedGrid.grid[chosenArmada.boats[i].y + j][chosenArmada.boats[i].x] = HIT;
                    }

                    break;
                default:
                    //error
                    printf("Unexpected direction : %c for : %s\n", chosenArmada.boats[i].direction,
                           chosenArmada.boats[i].name);
                    break;
            }

        }

    }

    return translatedGrid;
}