//
// Created by kenan.augsburger on 06.03.2020.
//

#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/**
 * pauses the program until the user presses enter
 */
void pause() {
    //wait for input to return
    printf("\n");
    printf("press any key to return\n");
    fflush(stdin);
    getch();
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
 * @warning avoid 0 as min value as letters
 * gets an int value from user
 * @param min value returned
 * @param max value returned
 * @return
 */
int getInt(int min, int max) {
    char string[2];
    int selection;

    //visual indicator
    printf(": ");

    //clean string to long
    do {
        fflush(stdin);
        scanf("%s", string);
        selection = stringToInt(string, max);
    } while (selection < min || selection > max);

    return selection;
}

//TODO:Check for bugs
/**
 *
 * @param string
 * @return int from 1 to max or 0 if there were no int
 */
int stringToInt(char *string, int maxReturnedValue) {
    char *pointer = NULL;
    int intValue;
    intValue = strtol(string, &pointer, maxReturnedValue + 1);
    return intValue;
}

/**
 * @warning avoid 0 as min value as letters
 * gets a char from user and translates it to int
 * @param min value returned
 * @param max value returned
 * @return intValue
 */
int getIntFromChar(int min, int max) {
    char charInput;
    int selection;

    //visual indicator
    printf(": ");

    //clean string to long
    do {
        fflush(stdin);
        scanf("%c", &charInput);
        selection = charToInt(charInput);
    } while (selection < min || selection > max);

    return selection;
}

/**
 *
 * @param string
 * @return int translated from letter or 0 if the passed char doesn't contain letters
 */
int charToInt(char letter) {
    int intValue = 0;

    /*uppercase letters*/
    if (letter >= 'A' && letter <= 'Z') {
        intValue = letter - 'A' + 1;
    }
        /*lowercase letters*/
    else if (letter >= 'a' && letter <= 'z') {
        intValue = letter - 'a' + 1;
    }
    return intValue;
}

/**
 *
 * @param intValue
 * @return a char from A=1, B=2 => ...
 */
char intToChar(int intValue) {
    char letter;

    letter = 'A' - 1 + intValue;

    return letter;
}

void offsetX(int offset) {

    for (int i = 0; i < offset; ++i) {
        printf(" ");
    }

}

void offsetY(int offset) {

    for (int i = 0; i < offset; ++i) {
        printf("\n");
    }

}