/**
 * this library contains various utility functions
 * requires {stdio.h,stdlib.h,string.h,stdbool.h}
 */


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

/**
 * get a clean int value from a user selection
 * @param min number in the selection
 * @param max number in the selection
 * @return
 */
int intSelector(int min,int max){
    char str[3];
    char *ptr = NULL;
    int selection;

    do {
        fflush(stdin);
        scanf("%s", str);
        selection = strtol(str, &ptr, max + 1);
    } while (selection < min || selection > max);

    return selection;
}

#endif //BATTLESHIPS_UTILITIES_H
