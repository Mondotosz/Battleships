//
// Created by kenan.augsburger on 06.03.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "utilities/utilities.h"
#include "utilities/logs.h"
#include "score.h"
#include "authentication.h"
#include "game.h"

/**
 * Game menu
 */
void gameHub(users player) {
    int i = 0;
    int selection;

    runtimeLog(INFO, "entered gameHub()");

    //option listing
    system("cls");
    printf("%sGame mode%s\n", T_BOLD, T_RESET);
    printf("\n");
    printf("%d - random map\n", ++i);
    printf("%d - create\n", ++i);
    printf("%d - list\n", ++i);
    printf("%d - back\n", ++i);
    printf("\n");

    selection = getInt(1, i);

    switch (selection) {
        case 1:
            game(player, RANDOM_GEN);
            break;
        case 2:
            printf("Map creation not yet implemented\n");
            pause();
            break;
        case 3:
            printf("Map listing not yet implemented");
            pause();
            break;
        default:
            break;
    }

    runtimeLog(INFO, "exited gameHub()");
}

/**
 * randomly generated game
 * @param player
 */
void game(users player, char mode) {
    char buffer[8];
    bool win = false;
    scores currentScore;
    grids stateGrid;
    grids checkGrid;
    armada fleet;

    system("cls");

    //setup
    switch (mode) {
        case RANDOM_GEN:
            printf("%sSetup%s\n", T_BOLD, T_RESET);
            printf("\n");
            printf("Grid size (min h8 / max z26)\n");

            do {
                fflush(stdin);
                fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                stateGrid.maxX = stringToInt(buffer);
                stateGrid.maxY = base26(buffer);
            } while (stateGrid.maxX < 8 || stateGrid.maxY < 8 || stateGrid.maxX > MAX_X || stateGrid.maxY > MAX_Y);
            //gets a randomized armada structure fitting the grid
            fleet = getRandomFleet(stateGrid);
            //translates its boats to grid coordinates
            checkGrid = armadaToGrid(fleet, stateGrid);
            break;
        case PRE_MADE:
            checkGrid = getMap("test");
            break;
        default:
            break;
    }


    for (int y = 0; y < stateGrid.maxY; ++y) {
        for (int x = 0; x < stateGrid.maxX; ++x) {
            stateGrid.grid[y][x] = UNCHECKED;
        }
    }



    //defaults miss count to 0
    currentScore.misses = 0;

    //game
    do {
        //displays the grid before firing
        displayGrid(checkGrid);

        //gets and displays the stats
        currentScore = missCount(stateGrid);
        offsetY(2);
        offsetX(4);
        printf("misses : %d\n", currentScore.misses);

        //select the shooting coordinates
        stateGrid = fire(stateGrid);

        //compare the 2 grids
        stateGrid = checkState(stateGrid, checkGrid);

        //check if it's a win
        win = checkWin(stateGrid, checkGrid);

    } while (win == false);

    //displays the end result
    displayResult(player, currentScore);

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
    for (int m = 0; m < displayedGrid.maxX * 3 + 2; ++m) {
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
    for (int l = 1; l < displayedGrid.maxX + 1; ++l) {
        printf("%2d%c", l, 186);
    }
    printf("\n");
    for (int y = 0; y < displayedGrid.maxY; ++y) {

        //vertical gap
        offsetX(xOffsetValue);
        printf("%c", 204);
        for (int k = 0; k < displayedGrid.maxX * 3 + 2; ++k) {
            if ((k + 1) % 3 == 0) {
                printf("%c", 206);
            } else {
                printf("%c", 205);
            }
        }
        printf("%c\n", 185);

        //side letter indicators
        offsetX(xOffsetValue);
        printf("%c %c%c", 186, intToChar(y + 1), 186);

        //displays cell state
        for (int x = 0; x < displayedGrid.maxX; ++x) {
            switch (displayedGrid.grid[y][x]) {
                case UNCHECKED:
                    printf("  ");
                    break;
                case MISS:
                    printf("%s%c%c%s", T_CYAN, 176, 176, T_RESET);
                    break;
                case HIT:
                    printf("%s%c%c%s", T_RED, 219, 219, T_RESET);
                    break;
                default:
                    runtimeLog(WARNING, "Unexpected value grid[%d][%d]=%d", y, x, displayedGrid.grid[y][x]);
            }
            printf("%c", 186);
        }
        printf("\n");
    }

    //grid bottom
    offsetX(xOffsetValue);
    printf("%c", 200);
    for (int m = 0; m < displayedGrid.maxX * 3 + 2; ++m) {
        if ((m + 1) % 3 == 0) {
            printf("%c", 202);
        } else {
            printf("%c", 205);
        }
    }
    printf("%c\n", 188);

}

/**
 * changes grid state on chosen coordinates
 * @param map
 * @return
 */
grids fire(grids map) {
    int x;
    int y;
    char buffer[16];

    do {

        do {
            //asks for xy coordinates and convert them
            offsetY(2);
            offsetX(4);
            printf("coordinates : ");
            fflush(stdin);
            fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            x = stringToInt(buffer);
            y = base26(buffer);
        } while (y < 1 || y > map.maxY || x < 1 || x > map.maxX);
        x -= OFFSET;
        y -= OFFSET;

        //check whether the cell was already checked
        if (map.grid[y][x] != UNCHECKED) {
            printf("\n");
            printf("You already checked this cell !\n");
        }

    } while (map.grid[y][x] != UNCHECKED);

    //puts them in map
    map.grid[y][x] = CHECKING;

    runtimeLog(INFO, "player shot at x : %d y : %d", x, y);

    return map;
}

//TODO:Check grid without translating => in game info on which boat was sunk

/**
 * compares the 2 grids and updates targeted coordinates
 * @param stateGrid
 * @param checkGrid
 * @return updated grid
 */
grids checkState(grids stateGrid, grids checkGrid) {
    for (int y = 0; y < stateGrid.maxY; ++y) {
        for (int x = 0; x < stateGrid.maxX; ++x) {

            //seeks the cell which was shot
            if (stateGrid.grid[y][x] == CHECKING) {

                //changes the cell state
                stateGrid.grid[y][x] = checkGrid.grid[y][x];

                //displays a message accordingly
                switch (stateGrid.grid[y][x]) {
                    case MISS:
                        runtimeLog(INFO, "Miss");
                        break;
                    case HIT:
                        runtimeLog(INFO, "Hit");
                        break;
                    default:
                        runtimeLog(ERROR, "unexpected state : %d", stateGrid.grid[y][x]);
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

    //compares both grids and returns true if every cell with a boat has been hit
    for (int y = 0; y < stateGrid.maxY; ++y) {
        for (int x = 0; x < stateGrid.maxX; ++x) {
            if (checkGrid.grid[y][x] == HIT && stateGrid.grid[y][x] != HIT) {
                win = false;
            }
        }
    }

    if (win) runtimeLog(INFO, "player won");

    return win;
}

/**
 * displays a grid from its values
 * @param player
 * @param score
 */
void displayResult(users player, scores score) {
    system("cls");

    //displays the result text depending on the user status
    if (player.authenticated) {
        printf("Well done %s !\n", player.nickname);
    } else {
        printf("Well done !\n");
    }

    printf("\n");
    printf("score : %d", score.misses);
    printf("\n");
    pause();

    //if the user didn't authenticate before playing
    system("cls");
    if (!player.authenticated) {
        printf("\n");
        printf("Would you like to save your score ?");

        //authenticate the user if he wants to save the score
        if (trueFalse()) {
            player = authenticateUser(player);
        }
    }

    //saves the score if the user is authenticated
    if (player.authenticated) {
        strncpy(score.nickname, player.nickname, sizeof(score.nickname) / sizeof(score.nickname[0]));
        newScore(score);
    }
}

/**
 * counts how many miss the user had
 * @param map
 * @return
 */
scores missCount(grids map) {
    scores currentScore;
    currentScore.misses = 0;

    //counts every miss
    for (int y = 0; y < map.maxY; ++y) {
        for (int x = 0; x < map.maxX; ++x) {
            if (map.grid[y][x] == MISS) {
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
armada getRandomFleet(grids grid) {
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
                fleet.boats[cBoat].y = 1 + rand() % (grid.maxY - fleet.boats[cBoat].length - 1);
                fleet.boats[cBoat].x = 1 + rand() % grid.maxX - 1;
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
                fleet.boats[cBoat].x = 1 + rand() % (grid.maxX - fleet.boats[cBoat].length - 1);
                fleet.boats[cBoat].y = 1 + rand() % grid.maxY - 1;
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
                   fleet.boats[k].direction, fleet.boats[k].x + 1, fleet.boats[k].y + 1);

    }

    return fleet;
}

/**
 * translates armada structure to grid structure
 * @warning isn't optimal as we always have 2 grids + the fleet on the buffer
 * @param chosenArmada
 * @return
 */
grids armadaToGrid(armada chosenArmada, grids map) {
    grids translatedGrid = map;

    //defaults every values to MISS
    for (int y = 0; y < map.maxY; ++y) {
        for (int x = 0; x < map.maxX; ++x) {
            translatedGrid.grid[y][x] = MISS;
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

//TODO: Map listing
//TODO: Map creation


/**
 * gets the list of maps from a file
 * @return list
 */
mapList getMapList() {
    FILE *fp;
    char c;
    int i = 0;

    //defaults list
    mapList list;
    list.range = 0;
    list.maps->name[0] = '\0';
    list.maps->author[0] = '\0';
    list.maps->exist = false;

    fp = fopen(MAP_LIST_FILE, "r");
    if (fp != NULL) {
        do {
            c = (char) fgetc(fp);
            if (c != '\0') {

                if (c == ';') {
                    i++;
                } else {

                    switch (i) {
                        case 0:
                            //map name
                            strncat(list.maps[list.range].name, &c,
                                    sizeof(list.maps[list.range].name) / sizeof(list.maps[list.range].name[0]));
                            break;
                        case 1:
                            //map author
                            strncat(list.maps[list.range].author, &c,
                                    sizeof(list.maps[list.range].author) / sizeof(list.maps[list.range].author[0]));
                            break;
                        case 2:
                            //exists and goes for the next one
                            i = 0;
                            list.maps[list.range].exist = true;
                            list.range++;
                            break;
                        default:
                            break;
                    }

                }


            }


            //name

            //author

            //exist


        } while (c != '\0');

    } else {
        fp = fopen(MAP_LIST_FILE, "w");
    }
    fclose(fp);

    return list;
}

/**
 * returns a grid from files
 * @param mapName
 * @return
 */
grids getMap(char *mapName) {
    char path[32] = "maps/";
    grids savedMap;
    FILE *fp; //file pointer
    char c;
    char buffer[64];
    int x = 0;
    int y = 0;

    //concatenate file path
    strncat(path, mapName, strlen(mapName) + 1);
    strncat(path, ".map", strlen(".map") + 1);

    //read from target file
    fp = fopen(path, "r");
    if (fp == NULL) {
        runtimeLog(WARNING, "map not found : %s", path);
        exit(2);
    } else {

        //get map max X
        buffer[0] = '\0';
        do {
            c = (char) fgetc(fp);

            if (c != ';') {
                strncat(buffer, &c, sizeof(buffer) / sizeof(buffer[0]));
            } else {
                savedMap.maxX = stringToInt(buffer);
            }

        } while (c != ';');

        //get map max Y
        buffer[0] = '\0';
        do {
            c = (char) fgetc(fp);

            if (c != ';') {
                strncat(buffer, &c, sizeof(buffer) / sizeof(buffer[0]));
            } else {
                savedMap.maxY = stringToInt(buffer);
                break;
            }

        } while (c != ';');

        //get map state
        do {

            do {
                c = (char) fgetc(fp);
            } while (c != '\0' && !isdigit(c));

            if (c != '\0') {
                savedMap.grid[y][x] = (int) c - '0';
            }

            if (x < savedMap.maxX - 1) {
                x++;
            } else if (y < savedMap.maxY - 1) {
                y++;
                x = 0;
            } else {
                break;
            }

        } while (c != '\0');


    }
    fclose(fp);

    return savedMap;
}