//
// Created by kenan.augsburger on 06.03.2020.
//

#include "utilities.h"
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

/**
 * pauses the program until the user presses enter
 * @warning values from getch are transferred to a buffer to avoid corrupting the next input
 * @warning workaround needs a definite fix
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
 * an alternative for strtol / atoi which reads digits from right to left, ignoring chars other than digits
 * @param string
 * @return returns the integers found in a string
 */
int stringToInt(char *string) {
    int result = 0;
    int count = 1;

    //parses the string for digits
    for (int i = (int) (strlen(string)); i >= 0; --i) {
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

    //make the string all lower cases to ease the process
    strlwr(string);

    //parses the string for alphabet chars
    for (int i = (int) (strlen(string)); i >= 0; --i) {
        if (isalpha(string[i])) {
            result += (string[i] - 'a' + 1) * count;
            count *= 26;
        }
    }

    return result;
}

/**
 * translates an integer value to alphabet
 * @warning Doesn't support values higher than 26, will be replaced for the final version
 * @param intValue
 * @return a char from A=1, B=2 => ...
 */
char intToChar(int intValue) {
    char letter;

    letter = 'A' - 1 + intValue;

    return letter;
}

/**
 * offset text horizontally
 * @warning will be replaced with text formatting directly in the program in the end
 * @param offset
 */
void offsetX(int offset) {
    printf("%*s", offset, "");
}

/**
 * offset the text vertically
 * @param offset
 */
void offsetY(int offset) {

    for (int i = 0; i < offset; ++i) {
        printf("\n");
    }

}