//
// Created by mondotosz on 15/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include "logs.h"

/**
 * logs message to runtime.log file
 * @param logType supports INFO,WARNING,ERROR
 * @param string
 * @param ... basic formatting arguments %c => char
 */
void runtimeLog(char logType, char *string, ...) {
    char *p;
    va_list argList;
    char *s;
    char c;
    int i;
    char stringBuffer[256];
    char formattedString[256];
    FILE *filePointer;
    time_t t;
    struct tm *tmp;
    char currentTime[50];

    fflush(stdin);
    formattedString[0] = '\0';

    //parses through args
    va_start(argList, string);

    for (p = string; *p != '\0'; p++) {
        if (*p != '%')
            strncat(formattedString, p, 1);
        else {
            switch (*++p) {
                case 'c':
                    c = va_arg(argList, int);
                    strncat(formattedString, &c, 1);
                    break;
                case 'd':
                    i = va_arg(argList, int);
                    strncat(formattedString, itoa(i, stringBuffer, 10), sizeof(stringBuffer));//radix 10 for base 10
                    break;
                case 's':
                    s = va_arg(argList, char *);
                    strncat(formattedString, s, sizeof(formattedString) / sizeof(formattedString[0]));
                    break;
                case 'x':
                    i = va_arg(argList, int);
                    strncat(formattedString, itoa(i, stringBuffer, 16), sizeof(stringBuffer));//radix 16 for base 16
                    break;
                case '%':
                    strncat(formattedString, "%", 2);
                    break;
            }
        }
    }

    va_end(argList);


    //save log
    filePointer = fopen(LOGS_FILE, "a");
    if (filePointer == NULL) {
        filePointer = fopen(LOGS_FILE, "w");
    }

    //time
    time(&t);
    tmp = localtime(&t);
    strftime(currentTime, sizeof(currentTime), "%c", tmp);
    fprintf(filePointer, "%s ", currentTime);

    //log type
    switch (logType) {
        case INFO:
            fprintf(filePointer, "# info : ");
            break;
        case WARNING:
            fprintf(filePointer, "# warning : ");
            break;
        case ERROR:
            fprintf(filePointer, "# error : ");
            break;
        default:
            fprintf(filePointer, "# unexpected logType argument : %c\n", logType);
            logType = UNEXPECTED;
            break;
    }

    //log message
    if (logType != UNEXPECTED) {
        fprintf(filePointer, "%s\n", formattedString);
    }

    fclose(filePointer);

}