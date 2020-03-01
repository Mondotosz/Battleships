/**
 * this library contains various utility functions
 * requires {stdio.h,stdlib.h,string.h,stdbool.h}
 */


#ifndef BATTLESHIPS_UTILITIES_H
#define BATTLESHIPS_UTILITIES_H

/**
 * asks for a boolean choice from the user and returns it
 * @param trueChar awaited true input
 * @param falseChar awaited false input
 * @return true/false
 */
bool trueFalse() {
    char answer;
    bool result;

    //displays the two available answers
    printf("(%s/%s)\n", displayLang.trueString, displayLang.falseString);
    printf(": ");

    //asks until the answer is valid
    do {
        fflush(stdin);
        scanf("%s", &answer);
    } while (strcmp(&answer, displayLang.trueString) != 0 && strcmp(&answer, displayLang.falseString) != 0);

    //compare the answer in order to return true or false
    if (strcmp(&answer, displayLang.trueString) == 0) {
        result = true;
    } else {
        result = false;
    }

    return result;
}

/**
 * gets an uppercase char input and returns its numerical equivalent
 * @param min A=0
 * @param max Z=25
 * @return converted char
 */
int charSelector(int min/*min int value*/, int max/*max int value*/) {
    char selection;
    int convertedSelection;

    do {
        fflush(stdin);
        scanf("%c", &selection);//gets a char
        selection -= 65;//uppercase A=>0
    } while (selection < min || selection > max);

    //puts the integer value of selection into convertedSelection
    convertedSelection = (int) (selection);

    return convertedSelection;
}

/**
 * get a clean int value from a user selection
 * @param min number in the selection
 * @param max number in the selection
 * @return selection value
 */
int intSelector(int min, int max) {
    char str[3];
    char *ptr = NULL;
    int selection;

    //gets a valid input from user
    do {
        fflush(stdin);
        scanf("%s", str);//stores it as string
        selection = strtol(str, &ptr, max + 1);//extract the int(long int) value from it
    } while (selection < min || selection > max);

    return selection;
}

/**
 * checks if the directories exist
 * @return true if there is an error
 */
bool dirCheck() {
    bool check = false;
    DIR *dir;

    system("cls");

    //languages check
    dir = opendir(languagesPath[0].path);
    if (dir) {
        //Directory exists
        closedir(dir);
    } else if (ENOENT == errno) {
        //Directory doesn't exists
        check = true;
        printf("%s does not exist\n", languagesPath[0].path);
    } else {
        //Can't open directory
        check = true;
        printf("Couldn't open : %s\n", languagesPath[0].path);
    }

    //maps check


    if (check)
        system("pause");

    return check;
}

/**
 * checks if the various languages files exist
 * @return true if there's an error
 */
bool languageFileCheck(language checkingLanguage) {
    bool check = false;
    char filePath[MAX_PATH_LENGTH + 1 + MAX_ACRONYM_LENGTH + MAX_EXTENSION_LENGTH];
    FILE *filePointer;

    system("cls");

    for (int i = 0; i < sizeof(languagesPath) / sizeof(languagesPath[0]); ++i) {
        //reset
        strcpy(filePath, "");
        //merge info
        strcat(filePath, languagesPath[i].path);
        strcat(filePath, "/");
        strcat(filePath, checkingLanguage.acronym);
        strcat(filePath, languagesPath[i].extension);

        filePointer = fopen(filePath, "r");
        if (filePointer) {
            fclose(filePointer);
        } else {
            check = true;
            printf("%s doesn't exist\n", filePath);
        }
    }

    if (check)
        system("pause");

    return check;
}

#endif //BATTLESHIPS_UTILITIES_H
