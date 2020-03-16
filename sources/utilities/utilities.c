//
// Created by kenan.augsburger on 06.03.2020.
//

#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

/**
 * pauses the program until the user presses enter
 */
void pause() {
    int buffer;
    //wait for input to return
    printf("\n");
    printf("press any key to return\n");
    fflush(stdin);
    //empties getch to avoid overflow
    buffer = getch();
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
        selection = stringToInt(string);
    } while (selection < min || selection > max);

    return selection;
}

/**
 *
 * @param string
 * @return int from 1 to max or 0 if there were no int
 */
int stringToInt(char *string) {
    int result = 0;
    int count = 1;

    //parses the string for digits
    for (int i = 0; i < (int) (strlen(string)); i++) {
        if (isdigit(string[i])) {
            result += (string[i] - '0') * count;
            count *= 10;
        }
    }

    return result;
}

/**
 * translates alphabet chars to int
 * @param string
 * @return
 */
int base26(char string[16]) {
    int result = 0;
    int count = 1;
    strlwr(string);

    for (int i = (int) (strlen(string)); i >= 0; --i) {
        if (isalpha(string[i])) {
            result += (string[i] - 'a' + 1) * count;
            count *= 26;
        }
    }

    return result;
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