//
// Created by mondotosz on 15/03/2020.
//

#ifndef BATTLESHIPS_LOGS_H
#define BATTLESHIPS_LOGS_H

#define LOGS_FILE "runtime.log"

#define ERROR 'e'
#define WARNING 'w'
#define INFO 'i'
#define UNEXPECTED 'u'


void runtimeLog(char logType, char string[255], ...);

#endif //BATTLESHIPS_LOGS_H
