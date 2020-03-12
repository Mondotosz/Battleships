//
// Created by mondotosz on 08/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities/utilities.h"
#include "score.h"

/**
 * displays scores from score file
 */
void displayScores() {
    scoreboard currentScoreboard;

    //setup
    system("cls");
    printf("Score\n");
    printf("\n");

    currentScoreboard = getScoreboard();

    if (currentScoreboard.range > 0) {
        for (int i = 0; i < currentScoreboard.range; ++i) {
            printf("nickname : %s \ttries : %d\n", currentScoreboard.existingScores[i].nickname,
                   currentScoreboard.existingScores[i].tries);
        }
    } else {
        printf("No scores yet!\n");
    }
    pause();

}

/**
 * gets the list of scores from a score file
 * @return listed scores
 */
scoreboard getScoreboard() {
    scoreboard currentScoreboard;
    FILE *filePointer;
    char cursor;
    char tempString[MAX_NICKNAME_LENGTH];
    char currentVar;
    currentScoreboard.range = 0;

    //opens file
    filePointer = fopen(SCOREBOARD_JSON, "r");
    if (filePointer == NULL) {
        filePointer = fopen(SCOREBOARD_JSON, "w");
    } else {

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
                                        strncpy(currentScoreboard.existingScores[currentScoreboard.range].nickname,
                                                tempString, MAX_NICKNAME_LENGTH);
                                        break;
                                    case TRIES:
                                        currentScoreboard.existingScores[currentScoreboard.range].tries = atoi(
                                                tempString);
                                        currentScoreboard.range++;
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

    return currentScoreboard;
}

void newScore(scores newScore) {
    FILE *filePointer;
    scoreboard currentScoreboard;

    //get current scoreboard
    currentScoreboard = getScoreboard();
    //add new score to the variable
    currentScoreboard.existingScores[currentScoreboard.range] = newScore;
    currentScoreboard.range++;

    filePointer = fopen(SCOREBOARD_JSON, "w");
    for (int i = 0; i < currentScoreboard.range; ++i) {
        fprintf(filePointer, "\"nickname\":\"%s\",\n", currentScoreboard.existingScores[i].nickname);
        fprintf(filePointer, "\"tries\":\"%d\",\n", currentScoreboard.existingScores[i].tries);
    }
    fclose(filePointer);

}