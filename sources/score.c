//
// Created by mondotosz on 08/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities/utilities.h"
#include "utilities/logs.h"
#include "score.h"

//TODO:make it more flexible with format specifier %*s

/**
 * displays scores from score file
 */
void displayScores() {
    scoreboard currentScoreboard;

    runtimeLog(INFO, "entered scoreboard()");

    //setup
    system("cls");
    printf("%sScore%s\n", T_BOLD, T_RESET);
    printf("\n");

    //gets the scoreboard
    currentScoreboard = getScoreboard();
    currentScoreboard = bubbleSortScoreboard(currentScoreboard);

    //displays its content
    if (currentScoreboard.range > 0) {

        //top border
        printf("%c", 201);
        for (int j = 0; j < 24; ++j) {
            if (j == 17) {
                printf("%c", 203);
            } else {
                printf("%c", 205);
            }
        }
        printf("%c\n", 187);

        //header
        printf("%c %-15s %cmisses%c\n", 186, "nickname", 186, 186);

        //separator
        printf("%c", 204);
        for (int j = 0; j < 24; ++j) {
            if (j == 17) {
                printf("%c", 206);
            } else {
                printf("%c", 205);
            }
        }
        printf("%c\n", 185);

        //scores
        for (int i = 0; i < currentScoreboard.range; ++i) {
            printf("%c %-15s %c %4d %c\n", 186, currentScoreboard.existingScores[i].nickname, 186,
                   currentScoreboard.existingScores[i].misses, 186);
        }

        //footer
        printf("%c", 200);
        for (int j = 0; j < 24; ++j) {
            if (j == 17) {
                printf("%c", 202);
            } else {
                printf("%c", 205);
            }
        }
        printf("%c\n", 188);


    } else {
        printf("No scores yet!\n");
    }

    pause();

    runtimeLog(INFO, "exited scoreboard()");
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
    filePointer = fopen(SCOREBOARD_FILE, "r");
    if (filePointer == NULL) {
        filePointer = fopen(SCOREBOARD_FILE, "w");
    } else {

        //gets the values in it
        tempString[0] = '\0';
        while (!feof(filePointer)) {

            do {
                fflush(stdin);
                cursor = (char) fgetc(filePointer);
            } while (cursor == ' ');

            //detects variable name
            if (cursor == '"') {

                //empty tempString
                tempString[0] = '\0';

                //get current variable
                do {
                    fflush(stdin);
                    cursor = (char) fgetc(filePointer);
                    if (cursor != '"') {
                        snprintf(tempString, sizeof(tempString), "%s%c", tempString, cursor);
                    }
                } while (cursor != '"');
                //on exit we get the var name
            }

            //translate chosen variable to a char usable in switch
            if (strcmp(tempString, "nickname") == 0) {
                currentVar = NICKNAME;
            } else if (strcmp(tempString, "misses") == 0) {
                currentVar = TRIES;
            } else {
                currentVar = ' ';
            }

            //if the variable is known then get its value
            if (currentVar != ' ') {
                do {
                    fflush(stdin);
                    cursor = (char) fgetc(filePointer);

                    //gets the value for the current variable
                    if (cursor == '"') {
                        tempString[0] = '\0';
                        do {
                            fflush(stdin);
                            cursor = (char) fgetc(filePointer);
                            if (cursor != '"') {
                                snprintf(tempString, sizeof(tempString), "%s%c", tempString, cursor);
                            } else {

                                //puts the value in the correct variable
                                switch (currentVar) {
                                    case NICKNAME:
                                        strncpy(currentScoreboard.existingScores[currentScoreboard.range].nickname,
                                                tempString,
                                                sizeof(currentScoreboard.existingScores[currentScoreboard.range].nickname)-1);
                                        break;
                                    case TRIES:
                                        currentScoreboard.existingScores[currentScoreboard.range].misses = stringToInt(
                                                tempString);
                                        currentScoreboard.range++;
                                        break;
                                }

                                tempString[0] = '\0';
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

    //exits on overflow to avoid scoreboard corruption
    if (strlen(newScore.nickname) > MAX_NICKNAME_LENGTH) {
        runtimeLog(ERROR, "score.nickname overflow : score wasn't saved");
        printf("\n");
        printf("ERROR : Check runtime.log\n");
        pause();
        exit(1);
    }

    //parses the newScore for unwanted inputs and removes them
    do {
        newScore.nickname[strcspn(newScore.nickname, "\n")] = '\0';
        newScore.nickname[strcspn(newScore.nickname, "\"")] = ' ';
    } while (strcspn(newScore.nickname, "\"") != strlen(newScore.nickname) &&
             strcspn(newScore.nickname, "\n") != strlen(newScore.nickname));

    //get current scoreboard
    currentScoreboard = getScoreboard();

    //add new score to the variable
    currentScoreboard.existingScores[currentScoreboard.range] = newScore;
    currentScoreboard.range++;

    //sort scores before saving
    currentScoreboard = bubbleSortScoreboard(currentScoreboard);

    //outputs the scoreboard to the file
    filePointer = fopen(SCOREBOARD_FILE, "w");
    for (int i = 0; i < currentScoreboard.range; ++i) {
        fprintf(filePointer, "\"nickname\":\"%s\",\n", currentScoreboard.existingScores[i].nickname);
        fprintf(filePointer, "\"misses\":\"%d\",\n", currentScoreboard.existingScores[i].misses);
    }

    fclose(filePointer);

    runtimeLog(INFO, "saved score");
}

/**
 * bubble sort algorithm to sort scores
 * @param unsortedScoreboard
 * @return
 */
scoreboard bubbleSortScoreboard(scoreboard unsortedScoreboard) {
    scores swapScore;
    bool isOrdered;

    //bubble sort moves the scores up by one if its value is lower than its upper neighbor
    do {
        isOrdered = true;
        for (int i = 0; i < unsortedScoreboard.range - 1; ++i) {
            if (unsortedScoreboard.existingScores[i].misses > unsortedScoreboard.existingScores[i + 1].misses) {
                swapScore = unsortedScoreboard.existingScores[i];
                unsortedScoreboard.existingScores[i] = unsortedScoreboard.existingScores[i + 1];
                unsortedScoreboard.existingScores[i + 1] = swapScore;
                isOrdered = false;
            }
        }
    } while (!isOrdered);

    runtimeLog(INFO, "sorted scoreboard");

    return unsortedScoreboard;
}