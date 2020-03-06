//
// Created by kenan.augsburger on 06.03.2020.
//

#include "utilities.h"
#include <stdio.h>
#include <string.h>

void pause() {
    //wait for input to return
    printf("\n");
    printf("press enter to return");
    fflush(stdin);
    getchar();
}

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