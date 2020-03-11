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

    filePointer = fopen(SCOREBOARD_FILE_NAME, "r");
    if (filePointer == NULL) {
        printf("%s doesn't exist", SCOREBOARD_FILE_NAME);
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

scoreboard getScoreboard() {
    scoreboard currentScoreboard;
    FILE *filePointer;
    char cursor;
    char tempString[50];
    char currentVar;
    int scoreID = 0;

    //opens file
    filePointer = fopen(SCOREBOARD_JSON, "r");
    if (filePointer == NULL) {
        printf("%s doesn't exist\n", SCOREBOARD_FILE_NAME);
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
                                    strcpy(currentScoreboard.existingScores[scoreID].nickname, tempString);
                                    break;
                                case TRIES:
                                    currentScoreboard.existingScores[scoreID].tries = atoi(tempString);
                                    scoreID++;
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
    for (int i = 0; i < scoreID - 1; ++i) {
        printf("nickname : %s\ttries : %d\n", currentScoreboard.existingScores[i].nickname,
               currentScoreboard.existingScores[i].tries);
    }
//    strcpy(currentScoreboard.existingScores[0].nickname, tempString);


    fclose(filePointer);

    return currentScoreboard;
}