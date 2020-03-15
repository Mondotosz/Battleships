//
// Created by mondotosz on 15/03/2020.
//

#include <stdio.h>
#include "logs.h"

void runtimeLog(char string[255], char logType) {
    FILE *filePointer;

    filePointer = fopen(LOGS_FILE, "a");
    if (filePointer == NULL) {
        filePointer = fopen(LOGS_FILE, "w");
    }

    switch (logType) {
        case INFO:
            fprintf(filePointer, "#info : %s\n", string);
            break;
        case WARNING:
            fprintf(filePointer, "#warning : %s\n", string);
            break;
        case ERROR:
            fprintf(filePointer, "#error : %s\n", string);
            break;
        default:
            fprintf(filePointer, "#error : unexpected log type\n");
            break;
    }

    fclose(filePointer);

}