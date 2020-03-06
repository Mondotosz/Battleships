//
// Created by kenan.augsburger on 06.03.2020.
//

#ifndef BATTLESHIPS_GAME_H
#define BATTLESHIPS_GAME_H

#define bool	_Bool
#define true	1
#define false	0

#define MAX_NICKNAME_LENGTH 16

typedef struct{
    char nickname[MAX_NICKNAME_LENGTH];
    bool authenticated;
}users;

void gameHub(users currentUser);

#endif //BATTLESHIPS_GAME_H
