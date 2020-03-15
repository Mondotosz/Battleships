//
// Created by mondotosz on 15/03/2020.
//

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "logs.h"

void runtimeLog(char string[255], char logType) {
    FILE *filePointer;
    time_t t;
    struct tm *tmp;
    char currentTime[50];
    char logTypeString[15];

    time(&t);

    tmp = localtime(&t);

    strftime(currentTime, sizeof(currentTime), "%c", tmp);

    filePointer = fopen(LOGS_FILE, "a");
    if (filePointer == NULL) {
        filePointer = fopen(LOGS_FILE, "w");
    }

    switch (logType) {
        case INFO:
            strncpy(logTypeString, "info", sizeof(logTypeString) / sizeof(logTypeString[0]));
            break;
        case WARNING:
            strncpy(logTypeString, "warning", sizeof(logTypeString) / sizeof(logTypeString[0]));
            break;
        case ERROR:
            strncpy(logTypeString, "error", sizeof(logTypeString) / sizeof(logTypeString[0]));
            break;
        default:
            logType = UNEXPECTED;
            break;
    }

    //log
    fprintf(filePointer, "%s ", currentTime);
    if (logType != UNEXPECTED) {
        fprintf(filePointer, "# %s : %s\n", logTypeString, string);
    } else {
        fprintf(filePointer, "# unexpected logType argument : %c\n", logType);
    }

    fclose(filePointer);

}