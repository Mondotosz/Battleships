//
// Created by kenan.augsburger on 06.03.2020.
//

#ifndef BATTLESHIPS_AUTHENTICATION_H
#define BATTLESHIPS_AUTHENTICATION_H

#define MAX_NICKNAME_LENGTH 16

typedef struct{
    char nickname[MAX_NICKNAME_LENGTH];
    bool authenticated;
}users;

users authenticateUser(users authenticatingUser);
users authenticationMenu(users currentUser);

#endif //BATTLESHIPS_AUTHENTICATION_H
