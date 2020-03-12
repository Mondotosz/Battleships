//
// Created by mondotosz on 08/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities/utilities.h"
#include "score.h"

//TODO:Write scores to files

void displayScores() {
    scoreboard currentScoreboard;

    //setup
    system("cls");
    printf("Score\n");
    printf("\n");

    currentScoreboard = getScoreboard();

    for (int i = 0; i < currentScoreboard.range; ++i) {
        printf("nickname : %s \ttries : %d\n", currentScoreboard.existingScores[i].nickname,
               currentScoreboard.existingScores[i].tries);
    }

    pause();

}

scoreboard getScoreboard() {
    scoreboard currentScoreboard;
    FILE *filePointer;
    char cursor;
    char tempString[50];
    char currentVar;
    currentScoreboard.range = 0;

    //opens file
    filePointer = fopen(SCOREBOARD_JSON, "r");
    if (filePointer == NULL) {
        printf("%s doesn't exist\n", SCOREBOARD_JSON);
        pause();
    }

    //gets the values in it
    strcpy(tempString, "");
    while (!feof(filePointer)) {
        fflush(stdin);
        fscanf(filePointer, "%c", &cursor);
        //detects variable name
        if (cursor == '"') {
            //empty tempString
            strcpy(tempString, "");
            //get current var
            do {
                fflush(stdin);
                fscanf(filePointer, "%c", &cursor);
                if (cursor != '"') {
                    strncat(tempString, &cursor, 1);
                }
            } while (cursor != '"');
            //on exit we get the var name
        }

        if (strcmp(tempString, "nickname") == 0) {
            currentVar = NICKNAME;
        } else if (strcmp(tempString, "tries") == 0) {
            currentVar = TRIES;
        } else {
            currentVar = ' ';
        }

        if (currentVar != ' ') {
            do {
                fflush(stdin);
                fscanf(filePointer, "%c", &cursor);
                if (cursor == '"') {
                    //empty tempString
                    strcpy(tempString, "");
                    //get value
                    do {
                        fflush(stdin);
                        fscanf(filePointer, "%c", &cursor);
                        if (cursor != '"') {
                            strncat(tempString, &cursor, 1);
                        } else {
                            switch (currentVar) {
                                case NICKNAME:
                                    strcpy(currentScoreboard.existingScores[currentScoreboard.range].nickname,
                                           tempString);
                                    break;
                                case TRIES:
                                    currentScoreboard.existingScores[currentScoreboard.range].tries = atoi(tempString);
                                    currentScoreboard.range++;
                                    break;
                                default:
                                    break;
                            }

                            strcpy(tempString, "");
                        }
                    } while (cursor != '"');
                }
            } while (cursor != '"');
        }

    }

    fclose(filePointer);

    return currentScoreboard;
}