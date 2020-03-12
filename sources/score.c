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

    //gets the scoreboard
    currentScoreboard = getScoreboard();

    //displays its content
    if (currentScoreboard.range > 0) {
        printf("%c", 201);
        for (int j = 0; j < 24; ++j) {
            printf("%c", 205);
        }
        printf("%c\n", 187);
        for (int i = 0; i < currentScoreboard.range; ++i) {
            printf("%c %15s : %4d %c\n", 186, currentScoreboard.existingScores[i].nickname,
                   currentScoreboard.existingScores[i].tries, 186);
        }
        printf("%c", 200);
        for (int j = 0; j < 24; ++j) {
            printf("%c", 205);
        }
        printf("%c\n", 188);
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
            if (strcmp(tempString, "nickname") == 0) {
                currentVar = NICKNAME;
            } else if (strcmp(tempString, "tries") == 0) {
                currentVar = TRIES;
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
                                //puts the value in the correct variable
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

/**
 * Adds a new score to the scoreboard file
 * @param newScore
 */
void newScore(scores newScore) {
    FILE *filePointer;
    scoreboard currentScoreboard;

    //get current scoreboard
    currentScoreboard = getScoreboard();
    //add new score to the variable
    currentScoreboard.existingScores[currentScoreboard.range] = newScore;
    currentScoreboard.range++;
    //outputs the scoreboard to the file
    filePointer = fopen(SCOREBOARD_JSON, "w");
    for (int i = 0; i < currentScoreboard.range; ++i) {
        fprintf(filePointer, "\"nickname\":\"%s\",\n", currentScoreboard.existingScores[i].nickname);
        fprintf(filePointer, "\"tries\":\"%d\",\n", currentScoreboard.existingScores[i].tries);
    }
    fclose(filePointer);

}