//
// Created by kenan.augsburger on 06.03.2020.
//

#ifndef BATTLESHIPS_UTILITIES_H
#define BATTLESHIPS_UTILITIES_H

#define bool    _Bool
#define true    1
#define false    0

void pause(void);

bool trueFalse(void);

int getInt(int min, int max);

int stringToInt(char *string, int maxReturnedValue);

int getIntFromChar(int min, int max);

int charToInt(char letter);

#endif //BATTLESHIPS_UTILITIES_H
