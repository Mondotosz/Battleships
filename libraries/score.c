//
// Created by mondotosz on 08/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities/utilities.h"
#include "score.h"

//TODO:Write scores to files
//TODO:Read scores from files

void displayScores() {
    FILE *filePointer;
    char tempString[16];
    int cursor;
    char swap;
    int currentScore = 0;
    scores scoreboard[MAX_RECORDED_SCORES];

    //setup
    system("cls");
    printf("Score\n");
    printf("\n");

    filePointer = fopen(SCOREBOARD, "r");
    if (filePointer == NULL) {
        printf("%s doesn't exist", SCOREBOARD);
        pause();
    }

    while (!feof(filePointer)) {
        //get nickname
        //reset variables
        strcpy(scoreboard[currentScore].nickname, "");
        cursor = ' ';
        //loop until ';'
        while (cursor != SEPARATOR && !feof(filePointer)) {
            cursor = fgetc(filePointer);
            swap = cursor;
            if (cursor != SEPARATOR && !feof(filePointer)) {
                strncat(scoreboard[currentScore].nickname, &swap, 1);
            }
        }

        //get score
        //reset variables
        strcpy(tempString, "");
        cursor = ' ';
        //loop until '\n'
        while (cursor != RETURN && !feof(filePointer)) {
            cursor = fgetc(filePointer);
            swap = cursor;
            if (cursor != RETURN && !feof(filePointer)) {
                strncat(tempString, &swap, 1);
            } else {
                scoreboard[currentScore].tries = atoi(tempString);
            }
        }
        //goes to the next score
        currentScore++;
    }
    fclose(filePointer);

    for (int i = 0; i < currentScore; ++i) {
        printf("%s\t: %d\n", scoreboard[i].nickname, scoreboard[i].tries);
    }

    pause();

}