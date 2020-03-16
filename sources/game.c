//
// Created by kenan.augsburger on 06.03.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utilities/utilities.h"
#include "utilities/logs.h"
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
        displayGrid(stateGrid);
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
        strncpy(currentScore.nickname, currentUser.nickname, MAX_NICKNAME_LENGTH - 1);
        newScore(currentScore);
    }

}

//TODO:use format specifiers to simplify display

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
    for (int l = 1; l < MAX_X + 1; ++l) {
        printf("%2d%c", l, 186);
    }
    printf("\n");
    for (int i = 0; i < MAX_Y; ++i) {

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
        printf("%c %c%c", 186, intToChar(i + 1), 186);

        //displays cell state
        for (int j = 0; j < MAX_X; ++j) {
            switch (displayedGrid.grid[j][i]) {
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
                    runtimeLog(WARNING, "Unexpected value grid[%d][%d]=%d", i, j, displayedGrid.grid[i][j]);
            }
            printf("%c", 186);
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

//TODO:fire takes both values at once

/**
 * changes grid state on chosen coordinates
 * @param stateGrid
 * @return
 */
grids fire(grids stateGrid) {
    int x;
    int y;
    char input[16];

    do {
        printf("\n");
        //asks for x coordinates
        offsetX(4);
        printf("x ");
        x = getInt(OFFSET, MAX_X);
        x -= OFFSET;

        do {
            //asks for y coordinates and convert them
            offsetX(4);
            printf("y ");
            fflush(stdin);
            scanf("%s", input);
            y = base26(input);
        } while (y < 1 || y > MAX_Y);
        y -= OFFSET;

        if (stateGrid.grid[x][y] != UNCHECKED) {
            printf("\n");
            printf("You already checked this cell !\n");
        }

    } while (stateGrid.grid[x][y] != UNCHECKED);

    //puts them in stateGrid
    stateGrid.grid[x][y] = CHECKING;

    runtimeLog(INFO, "player shot at x : %d y : %d", y, x);

    return stateGrid;
}

//TODO:Check grid without translating => in game info on which boat was sunk

/**
 * compares the 2 grids and updates targeted coordinates
 * @param stateGrid
 * @param checkGrid
 * @return updated grid
 */
grids checkState(grids stateGrid, grids checkGrid) {
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            if (stateGrid.grid[i][j] == CHECKING) {
                stateGrid.grid[i][j] = checkGrid.grid[i][j];
                switch (stateGrid.grid[i][j]) {
                    case MISS:
                        runtimeLog(INFO, "Miss");
                        break;
                    case HIT:
                        runtimeLog(INFO, "Hit");
                        break;
                    default:
                        runtimeLog(ERROR, "unexpected state : %d", stateGrid.grid[i][j]);
                        break;
                }
            }
        }
    }
    return stateGrid;
}

/**
 * checks if there are any boats left on the grid
 * @param stateGrid
 * @param checkGrid
 * @return true / false
 */
bool checkWin(grids stateGrid, grids checkGrid) {
    bool win = true;

    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            if (checkGrid.grid[i][j] == HIT && stateGrid.grid[i][j] != HIT) {
                win = false;
            }
        }
    }

    if (win) runtimeLog(INFO, "player won");

    return win;
}

/**
 * displays a grid from its values
 * @param currentUser
 * @param misses
 */
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

/**
 * counts how many miss the user had
 * @param currentGrid
 * @return
 */
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

/**
 * generates the 5 standard boats at random coordinates
 * @return random fleet
 */
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

    //initialize a random seed
    srand((unsigned) time(NULL));

    for (int cBoat = 0; cBoat < fleet.numberOfBoats; ++cBoat) {

        //loops until boats don't overlap, not optimal but needed
        do {
            overlap = false;

            //randomize the direction
            if (rand() % 2 == 0) {
                //gives random coordinates to a vertical boat
                fleet.boats[cBoat].direction = VERTICAL;
                fleet.boats[cBoat].y = 1 + rand() % (MAX_X - fleet.boats[cBoat].length - 1);
                fleet.boats[cBoat].x = 1 + rand() % MAX_Y - 1;
                fleet.boats[cBoat].exists = true;
                //check if it overlaps with any previous boat
                for (int pBoat = 0; pBoat < cBoat; ++pBoat) {

                    //depending on previous boats states
                    if (fleet.boats[pBoat].exists) {

                        switch (fleet.boats[pBoat].direction) {
                            case VERTICAL://parallel (current boat & past boat are vertical)
                                for (int cBoatL = 0; cBoatL < fleet.boats[cBoat].length; ++cBoatL) {
                                    for (int pBoatL = 0; pBoatL < fleet.boats[pBoat].length; ++pBoatL) {
                                        //check for each cell
                                        if (fleet.boats[cBoat].x == fleet.boats[pBoat].x &&
                                            fleet.boats[cBoat].y + cBoatL == fleet.boats[pBoat].y + pBoatL) {
                                            overlap = true;
                                        }
                                    }
                                }
                                break;

                            case HORIZONTAL://(current boat is vertical and past boat is horizontal)
                                for (int cBoatL = 0; cBoatL < fleet.boats[cBoat].length; ++cBoatL) {
                                    for (int pBoatL = 0; pBoatL < fleet.boats[pBoat].length; ++pBoatL) {
                                        //check for each cell
                                        if (fleet.boats[cBoat].x == fleet.boats[pBoat].x + pBoatL &&
                                            fleet.boats[cBoat].y + cBoatL == fleet.boats[pBoat].y) {
                                            overlap = true;
                                        }
                                    }
                                }
                                break;
                            default:
                                runtimeLog(ERROR, "Direction error : %c", fleet.boats[pBoat].direction);
                                break;
                        }

                    }

                }

            } else {
                //gives random coordinates to an horizontal boat
                fleet.boats[cBoat].direction = HORIZONTAL;
                fleet.boats[cBoat].x = 1 + rand() % (MAX_Y - fleet.boats[cBoat].length - 1);
                fleet.boats[cBoat].y = 1 + rand() % MAX_X - 1;
                fleet.boats[cBoat].exists = true;

                //check if it overlaps with any previous boat
                for (int pBoat = 0; pBoat < cBoat; ++pBoat) {

                    //depending on previous boats states
                    if (fleet.boats[pBoat].exists) {

                        switch (fleet.boats[pBoat].direction) {
                            case VERTICAL:
                                //parallel
                                for (int cBoatL = 0; cBoatL < fleet.boats[cBoat].length; ++cBoatL) {
                                    for (int pBoatL = 0; pBoatL < fleet.boats[pBoat].length; ++pBoatL) {
                                        //check for each cell
                                        if (fleet.boats[cBoat].y == fleet.boats[pBoat].y + pBoatL &&
                                            fleet.boats[cBoat].x + cBoatL == fleet.boats[pBoat].x) {
                                            overlap = true;
                                        }

                                    }
                                }
                                break;

                            case HORIZONTAL:
                                //cross
                                for (int cBoatL = 0; cBoatL < fleet.boats[cBoat].length; ++cBoatL) {
                                    for (int pBoatL = 0; pBoatL < fleet.boats[pBoat].length; ++pBoatL) {
                                        //check for each cell
                                        if (fleet.boats[cBoat].y == fleet.boats[pBoat].y &&
                                            fleet.boats[cBoat].x + cBoatL == fleet.boats[pBoat].x + pBoatL) {
                                            overlap = true;
                                        }
                                    }
                                }
                                break;
                            default:
                                runtimeLog(ERROR, "Direction error : %c", fleet.boats[pBoat].direction);
                                break;
                        }

                    }

                }

            }
            if (overlap)runtimeLog(WARNING, "overlap detected");//for statistics
        } while (overlap == true);

    }

    for (int k = 0; k < fleet.numberOfBoats; ++k) {
        //logs boats information
        runtimeLog(INFO, "generated boat[%d] name:%s length:%d direction:%c x:%d y:%d",
                   k, fleet.boats[k].name, fleet.boats[k].length,
                   fleet.boats[k].direction, fleet.boats[k].x, fleet.boats[k].y);

    }

    return fleet;
}

/**
 * translates armada structure to grid structure
 * @warning isn't optimal as we always have 2 grids + the fleet on the buffer
 * @param chosenArmada
 * @return
 */
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
                    runtimeLog(ERROR, "Unexpected direction : %c for : %s", chosenArmada.boats[i].direction,
                               chosenArmada.boats[i].name);
                    break;
            }

        }

    }

    return translatedGrid;
}