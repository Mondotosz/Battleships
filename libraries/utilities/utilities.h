/**
 * this library contains various utility functions
 * requires {stdio.h,stdlib.h,string.h,stdbool.h}
 */

//TODO: numbered choice function with strtol

#ifndef BATTLESHIPS_UTILITIES_H
#define BATTLESHIPS_UTILITIES_H

/**
 * asks for a yes or a no from the user
 * @return true/false
 */
bool yesOrNo() {
    char answer;
    bool result;

    printf("(y/n)\n");
    printf(": ");

    do {
        fflush(stdin);
        scanf("%s", &answer);
    } while (strcmp(&answer, "y") != 0 && strcmp(&answer, "n") != 0);

    if (strcmp(&answer, "y") == 0) {
        result = true;
    } else {
        result = false;
    }

    return result;
}

#endif //BATTLESHIPS_UTILITIES_H
