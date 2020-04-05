//
// Created by kenan.augsburger on 06.03.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <dir.h>
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
    int mapSelection;
    char buffer[8];
    armada fleet;
    grids checkGrid;
    mapList list;


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
            //standard randomly generated game
            system("cls");
            printf("%sSetup%s\n", T_BOLD, T_RESET);
            printf("\n");
            printf("Grid size (min h8 / max z26)\n");

            //gets the size of the map
            do {
                fflush(stdin);
                fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                checkGrid.maxX = stringToInt(buffer);
                checkGrid.maxY = base26(buffer);
            } while (checkGrid.maxX < 8 || checkGrid.maxY < 8 || checkGrid.maxX > MAX_X || checkGrid.maxY > MAX_Y);

            //gets a randomized armada structure fitting the grid
            fleet = getRandomFleet(checkGrid);

            //translates its boats to grid coordinates
            checkGrid = armadaToGrid(fleet, checkGrid);

            //launches the game with the newly generated map
            game(player, checkGrid);
            break;
        case 2:
            //create a new map
            saveMap(createMap(player));
            break;
        case 3:
            //play on a player made map
            list = getMapList();
            displayMapList(list);

            //lets the user choose the map he wants if any are available
            if (list.range > 0) {

                //available options
                printf("\n");
                printf("%-6s - select a map\n", "id");
                printf("%-6s - select a random map\n", "random");
                printf("%-6s - go back to the menu\n", "back");
                printf("\n");
                printf(": ");

                //gets the player choice
                do {
                    fflush(stdin);
                    fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), stdin);
                    buffer[strcspn(buffer, "\n")] = '\0';

                    mapSelection = stringToInt(buffer);

                } while ((mapSelection < 1 || mapSelection > list.range) && strcmp(buffer, "back") != 0 &&
                         strcmp(buffer, "random") != 0);

                //exit the menu if the player chose "back"
                if (strcmp(buffer, "back") != 0) {
                    if (mapSelection >= 1 && mapSelection <= list.range) {
                        //if the player chose a specific map
                        checkGrid = getMap(list.maps[mapSelection - 1].name);

                    } else {
                        //if the player chose to play a random map
                        srand((unsigned) time(NULL));
                        checkGrid = getMap(list.maps[rand() % list.range].name);
                    }
                    game(player, checkGrid);
                }


            } else {
                pause();
            }

            break;
        default:
            break;
    }

    runtimeLog(INFO, "exited gameHub()");
}

/**
 * Main game functions
 * @param player
 */
void game(users player, grids checkGrid) {

    bool win = false;
    scores currentScore;
    grids stateGrid;

    //state grid setup
    stateGrid.maxX = checkGrid.maxX;
    stateGrid.maxY = checkGrid.maxY;
    for (int y = 0; y < checkGrid.maxY; ++y) {
        for (int x = 0; x < checkGrid.maxX; ++x) {
            stateGrid.grid[y][x] = UNCHECKED;
        }
    }



    //defaults miss count to 0
    currentScore.misses = 0;

    //game
    do {
        //displays the grid before firing
        displayGrid(stateGrid);

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
    boat newBoat;

    //initialize a random seed
    srand((unsigned) time(NULL));

    for (int cBoat = 0; cBoat < fleet.numberOfBoats; ++cBoat) {
        newBoat = fleet.boats[cBoat];
        //loops until boats don't overlap, not optimal but needed
        do {

            //randomize the direction
            if (rand() % 2 == 0) {
                //gives random coordinates to a vertical boat
                newBoat.direction = VERTICAL;
                newBoat.y = 1 + rand() % (grid.maxY - fleet.boats[cBoat].length - 1);
                newBoat.x = 1 + rand() % grid.maxX - 1;

            } else {
                //gives random coordinates to an horizontal boat
                newBoat.direction = HORIZONTAL;
                newBoat.x = 1 + rand() % (grid.maxX - fleet.boats[cBoat].length - 1);
                newBoat.y = 1 + rand() % grid.maxY - 1;

            }
            newBoat.exists = true;
            //verifies whether the boat overlaps or not and regenerate it if needed
            overlap = checkOverlap(fleet, newBoat);

            if (overlap)runtimeLog(WARNING, "overlap detected");//for statistics


        } while (overlap);
        //adds the new boat to the fleet once it's good to go
        fleet.boats[cBoat] = newBoat;
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

    //defaults every values to MISS
    for (int y = 0; y < map.maxY; ++y) {
        for (int x = 0; x < map.maxX; ++x) {
            map.grid[y][x] = MISS;
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
                        map.grid[chosenArmada.boats[i].y][chosenArmada.boats[i].x + j] = HIT;
                    }

                    break;
                case VERTICAL:

                    //repeats for the length of the boat
                    for (int j = 0; j < chosenArmada.boats[i].length; ++j) {
                        map.grid[chosenArmada.boats[i].y + j][chosenArmada.boats[i].x] = HIT;
                    }

                    break;
                default:
                    runtimeLog(ERROR, "Unexpected direction : %c for : %s", chosenArmada.boats[i].direction,
                               chosenArmada.boats[i].name);
                    break;
            }

        }

    }

    return map;
}

/**
 * Displays content of a map list
 * @param list
 */
void displayMapList(mapList list) {

    runtimeLog(INFO, "displaying map list");

    //setup
    system("cls");
    printf("%sMaps%s\n", T_BOLD, T_RESET);
    printf("\n");

    //displays list
    if (list.range > 0) {

        //top border
        printf("%c", 201);
        for (int j = 0; j < 40; ++j) {
            if (j == 4 || j == 22) {
                printf("%c", 203);
            } else {
                printf("%c", 205);
            }
        }
        printf("%c\n", 187);

        //header
        printf("%c %-2s %c %-15s %c %-15s %c\n", 186, "id", 186, "map name", 186, "author", 186);

        //separator
        printf("%c", 204);
        for (int j = 0; j < 40; ++j) {
            if (j == 4 || j == 22) {
                printf("%c", 206);
            } else {
                printf("%c", 205);
            }
        }
        printf("%c\n", 185);

        //maps
        for (int i = 0; i < list.range; ++i) {
            printf("%c %2d %c %-15s %c %-15s %c\n", 186, i + 1, 186, list.maps[i].name, 186,
                   list.maps[i].author, 186);
        }

        //footer
        printf("%c", 200);
        for (int j = 0; j < 40; ++j) {
            if (j == 4 || j == 22) {
                printf("%c", 202);
            } else {
                printf("%c", 205);
            }
        }
        printf("%c\n", 188);


    } else {
        printf("No maps yet!\n");
    }

    runtimeLog(INFO, "displayed map list");

}

/**
 * gets the list of maps from a file
 * @return list
 */
mapList getMapList() {
    FILE *fp;
    char c;
    int i = 0;
    char buffer[32];

    //defaults list
    mapList list;
    list.range = 0;
    memset(list.maps->name, '\0', sizeof(list.maps->name));
    memset(list.maps->author, '\0', sizeof(list.maps->author));

    fp = fopen(MAP_LIST_FILE, "r");
    if (fp != NULL) {
        buffer[0] = '\0';
        do {
            fflush(stdin);
            c = (char) fgetc(fp);
            if (c != '\0' && list.range < MAX_MAPS) {

                if (c == ';') {
                    //copies the buffer content in the right variable
                    i++;
                    switch (i) {
                        case 1:
                            strncpy(list.maps[list.range].name, buffer,
                                    sizeof(list.maps[list.range].name) / sizeof(list.maps[list.range].name[0]) - 1);
                            break;
                        case 2:
                            strncpy(list.maps[list.range].author, buffer,
                                    sizeof(list.maps[list.range].author) / sizeof(list.maps[list.range].author[0]) - 1);
                            i = 0;
                            list.range++;
                            break;
                        default:
                            break;
                    }
                    buffer[0] = '\0';

                } else {
                    //appends each characters in a buffer until the cursor reaches a semicolon
                    strncat(buffer, &c, 1);
                    buffer[strcspn(buffer, "\n")] = '\0';

                }


            }

        } while (!feof(fp) && list.range < MAX_MAPS);

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
                strncat(buffer, &c, 1);
            } else {
                savedMap.maxX = stringToInt(buffer);
            }

        } while (c != ';');

        //get map max Y
        buffer[0] = '\0';
        do {
            c = (char) fgetc(fp);

            if (c != ';') {
                strncat(buffer, &c, 1);
            } else {
                savedMap.maxY = stringToInt(buffer);
                break;
            }

        } while (c != ';');

        //get map cell state
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

/**
 * Creates a new map
 * @param player
 * @return newMap
 */
map createMap(users player) {
    char buffer[20];
    map newMap;
    int x;
    int y;
    bool coordOK;
    mapList list = getMapList();
    bool alreadyExist;
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
    boat newBoat;


    //create map
    //pick the size
    system("cls");
    printf("%sSetup%s\n", T_BOLD, T_RESET);
    printf("\n");
    printf("Grid size (min h8 / max z26)\n");

    do {
        fflush(stdin);
        fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        newMap.content.maxX = stringToInt(buffer);
        newMap.content.maxY = base26(buffer);
    } while (newMap.content.maxX < 8 || newMap.content.maxY < 8 || newMap.content.maxX > MAX_X ||
             newMap.content.maxY > MAX_Y);

    //defaults every values to MISS
    for (int i = 0; i < newMap.content.maxY; ++i) {
        for (int j = 0; j < newMap.content.maxX; ++j) {
            newMap.content.grid[i][j] = MISS;
        }
    }

    //boats position
    for (int cBoat = 0; cBoat < fleet.numberOfBoats; ++cBoat) {

        //preview
        displayGrid(newMap.content);

        printf("\n");
        printf("place the %s (length %d)\n", fleet.boats[cBoat].name, fleet.boats[cBoat].length);
        newBoat = fleet.boats[cBoat];


        do {

            //asks for boat direction
            do {
                printf("direction (H/V) : ");
                fflush(stdin);
                fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                buffer[0] = (char) toupper(buffer[0]);

            } while (buffer[0] != HORIZONTAL && buffer[0] != VERTICAL);

            newBoat.direction = buffer[0];

            do {
                coordOK = true;
                //asks for xy coordinates and convert them
                printf("coordinates : ");
                fflush(stdin);
                fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                x = stringToInt(buffer);
                y = base26(buffer);

                //verifies whether the input is valid
                if (newBoat.direction == VERTICAL) {
                    if (y < 1 || y > newMap.content.maxY - fleet.boats[cBoat].length + 1 || x < 1 ||
                        x > newMap.content.maxX) {
                        coordOK = false;
                    }
                } else {
                    if (y < 1 || y > newMap.content.maxY || x < 1 ||
                        x > newMap.content.maxX - fleet.boats[cBoat].length + 1) {
                        coordOK = false;
                    }

                }

            } while (!coordOK);

            //offsets the values to the grid
            newBoat.x = x - 1;
            newBoat.y = y - 1;
            newBoat.exists = true;

            //checks for overlap
            overlap = checkOverlap(fleet, newBoat);

            if (overlap) {
                printf("Boat overlaps another, please retry\n");
            }

        } while (overlap);

        //adds the new boat to the fleet
        fleet.boats[cBoat] = newBoat;
        //updates the map preview
        newMap.content = armadaToGrid(fleet, newMap.content);
    }

    //final preview of the map
    system("cls");
    displayGrid(newMap.content);
    printf("\n");

    //name map
    printf("Name your map\n");
    printf("\n");
    printf(": ");

    //gets the name
    do {
        fflush(stdin);
        fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        do {
            buffer[strcspn(buffer, ";")] = '\0';
        } while (strcspn(buffer, ";") != strlen(buffer));

        //verifies if it's available
        alreadyExist = false;
        for (int i = 0; i < list.range; ++i) {
            if (strcmp(buffer, list.maps[i].name) == 0) {
                alreadyExist = true;
                printf("Map already exists\n");
                printf(": ");
            }
        }

    } while (alreadyExist == true);

    //saves the name
    strncpy(newMap.name, buffer, sizeof(newMap.name) - 1);

    //saves the author name
    if (!player.authenticated) {
        player = authenticateUser(player);
    }
    strncpy(newMap.author, player.nickname,
            sizeof(newMap.author) / sizeof(newMap.author[0]));

    return newMap;
}

/**
 * Saves the given map in the map folder and lists it as available
 * @param newMap
 */
void saveMap(map newMap) {
    FILE *fp;
    mapList list = getMapList();
    char path[32] = MAP_FOLDER;

    //creates the map folder if it didn't exist
    mkdir("maps");

    //saves the map
    //concatenate the file path
    strncat(path, newMap.name, strlen(newMap.name));
    strncat(path, MAP_EXTENSION, sizeof(MAP_EXTENSION));

    fp = fopen(path, "w");

    //write maxX and maxY
    fprintf(fp, "%d;%d;\n", newMap.content.maxX, newMap.content.maxY);

    //saves raw grid
    for (int y = 0; y < newMap.content.maxY; ++y) {
        for (int x = 0; x < newMap.content.maxX; ++x) {
            fprintf(fp, "%d", newMap.content.grid[y][x]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    //updates list
    if (list.range == 50) {
        list.range--;
    }

    for (int i = list.range; i > 0; --i) {
        list.maps[i] = list.maps[i - 1];
    }
    list.maps[0] = newMap;
    list.range++;

    fp = fopen(MAP_LIST_FILE, "w");

    //rewrites the map list
    for (int i = 0; i < list.range; ++i) {
        fprintf(fp, "%s;%s;\n", list.maps[i].name, list.maps[i].author);
    }

    fclose(fp);

}

/**
 * check whether the new boat overlaps with the old ones
 * @param fleet
 * @param newBoat
 * @return true if  there's an overlap
 */
bool checkOverlap(armada fleet, boat newBoat) {
    bool overlap = false;

    for (int cBoat = 0; cBoat < fleet.numberOfBoats; ++cBoat) {

        if (fleet.boats[cBoat].exists) {
            //check if it overlaps with any previous boat
            if (newBoat.direction == VERTICAL) {
                switch (fleet.boats[cBoat].direction) {
                    case VERTICAL://parallel (new boat & past boat are vertical)
                        for (int newBoatL = 0; newBoatL < newBoat.length; ++newBoatL) {
                            for (int cBoatL = 0; cBoatL < fleet.boats[cBoat].length; ++cBoatL) {
                                //check for each cell
                                if (newBoat.x == fleet.boats[cBoat].x &&
                                    newBoat.y + newBoatL == fleet.boats[cBoat].y + cBoatL) {
                                    overlap = true;
                                }
                            }
                        }
                        break;

                    case HORIZONTAL://(new boat is vertical and past boat is horizontal)
                        for (int newBoatL = 0; newBoatL < newBoat.length; ++newBoatL) {
                            for (int cBoatL = 0; cBoatL < fleet.boats[cBoat].length; ++cBoatL) {
                                //check for each cell
                                if (newBoat.x == fleet.boats[cBoat].x + cBoatL &&
                                    newBoat.y + newBoatL == fleet.boats[cBoat].y) {
                                    overlap = true;
                                }
                            }
                        }
                        break;
                    default:
                        runtimeLog(ERROR, "Direction error : %c", fleet.boats[cBoat].direction);
                        break;
                }


            } else {

                switch (fleet.boats[cBoat].direction) {
                    case VERTICAL:
                        //parallel
                        for (int newBoatL = 0; newBoatL < newBoat.length; ++newBoatL) {
                            for (int cBoatL = 0; cBoatL < fleet.boats[cBoat].length; ++cBoatL) {
                                //check for each cell
                                if (newBoat.y == fleet.boats[cBoat].y + cBoatL &&
                                    newBoat.x + newBoatL == fleet.boats[cBoat].x) {
                                    overlap = true;
                                }

                            }
                        }
                        break;

                    case HORIZONTAL:
                        //cross
                        for (int newBoatL = 0; newBoatL < newBoat.length; ++newBoatL) {
                            for (int cBoatL = 0; cBoatL < fleet.boats[cBoat].length; ++cBoatL) {
                                //check for each cell
                                if (newBoat.y == fleet.boats[cBoat].y &&
                                    newBoat.x + newBoatL == fleet.boats[cBoat].x + cBoatL) {
                                    overlap = true;
                                }
                            }
                        }
                        break;
                    default:
                        runtimeLog(ERROR, "Direction error : %c", fleet.boats[cBoat].direction);
                        break;
                }


            }

        }

    }

    return overlap;
}