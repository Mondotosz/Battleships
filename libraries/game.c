//
// Created by kenan.augsburger on 06.03.2020.
//

#include "game.h"
#include "authentication.h"
#include <stdio.h>
#include <string.h>

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

grids fire(grids stateGrid){
    int x;
    char y;
    int convertedY;

    printf("\n");
    //asks for x coordinates
    printf("x : ");
    do{
        scanf("%d",&x);
    }while (x<0||x>MAX_X);

    //TODO:create char to int as a separate function
    //asks for y coordinates and convert them
    printf("y : ");//char
    do{
        scanf("%c",&y);
        convertedY= (int)(y)-65;
    }while (convertedY<0||convertedY>MAX_Y);

    //puts them in stateGrid
    stateGrid.grid[x][convertedY]=CHECKING;

    return stateGrid;
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
