//
// Created by kenan.augsburger on 06.03.2020.
//

#include "game.h"
#include "authentication.h"

/**
 * main game function
 */
void gameHub(users currentUser){
    bool win=false;
    int stateGrid[9][9];
    //hard codded grid
    int checkGrid[9][9]={
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,1,0,0,0,0,0},
            {0,0,0,1,0,0,0,0,0},
            {0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0}
    };

    //setup
    for (int i = 0; i < sizeof(stateGrid)/ sizeof(stateGrid[0]); ++i) {
        for (int j = 0; j < sizeof(stateGrid)/ sizeof(stateGrid[0]); ++j) {
            stateGrid[i][j]=0;
        }
    }

    //game
    do{

    }while (win==false);

}
