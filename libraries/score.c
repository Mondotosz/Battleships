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
    char tempString[6];
    char c;
    int currentVar = NICKNAME;
    scores scoreboard[10];

    for (int i = 0; i < 9; ++i) {
        strcpy(scoreboard[i].nickname, "");
    }

    system("cls");

    filePointer = fopen(SCOREBOARD, "r");
    if (filePointer == NULL) {
        printf("%s doesn't exist", SCOREBOARD);
        pause();
    }

    while (!feof(filePointer)) {
        c = fgetc(filePointer);
        if (c != ';') {
            switch (currentVar) {
                case NICKNAME:
                    strncat(scoreboard[0].nickname, &c, 1);

                    break;
                case SCORE:

                    break;
                default:
                    printf("Unexpected currentVar : %d", currentVar);
            }
        } else {
            switch (currentVar) {
                case NICKNAME:
                    scoreboard[0]=stringToInt(tempString,100);
                    currentVar = SCORE;
                    break;
                case SCORE:
                    currentVar = NICKNAME;
                    break;
                default:
                    printf("Unexpected currentVar : %d", currentVar);

            }
        }
    }
    fclose(filePointer);

    printf("%s", scoreboard[0].nickname);

    pause();

}