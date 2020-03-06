//
// Created by kenan.augsburger on 06.03.2020.
//

#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * pauses the program until the user presses enter
 */
void pause() {
    //wait for input to return
    printf("\n");
    printf("press enter to return");
    fflush(stdin);
    getchar();
}

/**
 * gets a yes/no answer from the user
 * @return true/false
 */
bool trueFalse() {
    char answer;
    bool result;

    //displays the two available answers
    printf("(y/n)\n");
    printf(": ");

    //asks until the answer is valid
    do {
        fflush(stdin);
        scanf("%s", &answer);
    } while (strcmp(&answer, "y") != 0 && strcmp(&answer, "n") != 0);

    //compare the answer in order to return true or false
    if (strcmp(&answer, "y") == 0) {
        result = true;
    } else {
        result = false;
    }

    return result;
}

/**
 * gets an int value from user
 * @param min value returned
 * @param max value returned
 * @return
 */
int getCleanInt(int min, int max){
    char string[2];
    char *pointer = NULL;
    int selection;

    //user input
    printf("\n");
    printf(": ");

    //clean string to long
    do {
        fflush(stdin);
        scanf("%s", string);
        selection = strtol(string, &pointer, max + 1);
    } while (selection < min || selection > max);

    return selection;
}