//
// Created by kenan.augsburger on 06.03.2020.
//

#ifndef BATTLESHIPS_UTILITIES_H
#define BATTLESHIPS_UTILITIES_H

//ANSI text formatting
#define T_CYAN "\033[36m"
#define T_RED "\033[31m"
#define T_BOLD "\033[1m"
#define T_ITA "\033[3m"
#define T_RESET "\033[0m"

#define bool    _Bool
#define true    1
#define false    0

void pause();

#define TRUE_STR "yes"
#define FALSE_STR "no"

bool trueFalse(void);

int getInt(int min, int max);

int stringToInt(char *string);

char intToChar(int intValue);

void offsetX(int offset);

void offsetY(int offset);

int base26(char *string);

#endif //BATTLESHIPS_UTILITIES_H
