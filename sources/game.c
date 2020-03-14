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
    fleet = getArmada();
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

armada getArmada() {
    FILE *filePointer;
    char cursor;
    char tempString[MAX_NICKNAME_LENGTH];
    char currentVar;
    int currentBoat = 0;
    armada returnedArmada = {
            {
                    {"Destroyer", 2, 0, 0, HORIZONTAL, false},
                    {"Submarine", 3, 0, 0, HORIZONTAL, false},
                    {"Cruiser", 3, 0, 0, HORIZONTAL, false},
                    {"Battleship", 4, 0, 0, HORIZONTAL, false},
                    {"Carrier", 5, 0, 0, HORIZONTAL, false}
            },
            MAX_BOATS
    };


    //opens file
    filePointer = fopen(BOATS_JSON, "r");
    if (filePointer == NULL) {
        filePointer = fopen(BOATS_JSON, "w");
    } else {

        //gets the values in it
        strcpy(tempString, "");
        while (!feof(filePointer)) {
            do {
                fflush(stdin);
                fscanf(filePointer, "%c", &cursor);
            } while (cursor == ' ');
            //detects variable name
            if (cursor == '"') {
                //empty tempString
                strcpy(tempString, "");
                //get current variable
                do {
                    fflush(stdin);
                    fscanf(filePointer, "%c", &cursor);
                    if (cursor != '"') {
                        strncat(tempString, &cursor, 1);
                    }
                } while (cursor != '"');
                //on exit we get the var name
            }

            //translate chosen variable to a char usable in switch
            if (strcmp(tempString, "length") == 0) {
                currentVar = BOAT_LENGTH;
            } else if (strcmp(tempString, "direction") == 0) {
                currentVar = BOAT_DIRECTION;
            } else if (strcmp(tempString, "x") == 0) {
                currentVar = BOAT_X;
            } else if (strcmp(tempString, "y") == 0) {
                currentVar = BOAT_Y;
            } else if (strcmp(tempString, "exists") == 0) {
                currentVar = BOAT_EXISTS;
            } else {
                currentVar = ' ';
            }

            //if the variable is known then get its value
            if (currentVar != ' ') {
                do {
                    fflush(stdin);
                    fscanf(filePointer, "%c", &cursor);
                    //gets the value for the current variable
                    if (cursor == '"') {
                        strcpy(tempString, "");
                        do {
                            fflush(stdin);
                            fscanf(filePointer, "%c", &cursor);
                            if (cursor != '"') {
                                strncat(tempString, &cursor, 1);
                            } else {

                                //TODO:replace atoi to avoid problems
                                //puts the value in the correct variable
                                switch (currentVar) {
                                    case BOAT_LENGTH:
                                        returnedArmada.boat[currentBoat].length = atoi(tempString);
                                        break;
                                    case BOAT_DIRECTION:
                                        returnedArmada.boat[currentBoat].direction = tempString[0];
                                        break;
                                    case BOAT_X:
                                        returnedArmada.boat[currentBoat].x = atoi(tempString) - 1;
                                        break;
                                    case BOAT_Y:
                                        returnedArmada.boat[currentBoat].y = atoi(tempString) - 1;
                                        break;
                                    case BOAT_EXISTS:
                                        if (strcmp(tempString, "true") == 0) {
                                            returnedArmada.boat[currentBoat].exists = true;
                                        }
                                        currentBoat++;
                                        break;
                                }

                                strcpy(tempString, "");
                            }
                        } while (cursor != '"');
                    }
                } while (cursor != '"');
            }

        }
    }
    fclose(filePointer);

    return returnedArmada;
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
        if (chosenArmada.boat[i].exists) {

            //places them according to direction
            switch (chosenArmada.boat[i].direction) {
                case HORIZONTAL:

                    //repeats for the length of the boat
                    for (int j = 0; j < chosenArmada.boat[i].length; ++j) {
                        translatedGrid.grid[chosenArmada.boat[i].y][chosenArmada.boat[i].x + j] = HIT;
                    }

                    break;
                case VERTICAL:

                    //repeats for the length of the boat
                    for (int j = 0; j < chosenArmada.boat[i].length; ++j) {
                        translatedGrid.grid[chosenArmada.boat[i].y + j][chosenArmada.boat[i].x] = HIT;
                    }

                    break;
                default:
                    //error
                    printf("Unexpected direction : %c for : %s\n", chosenArmada.boat[i].direction,
                           chosenArmada.boat[i].name);
                    break;
            }

        }

    }

    return translatedGrid;
}