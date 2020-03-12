//
// Created by kenan.augsburger on 06.03.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utilities/utilities.h"
#include "authentication.h"

/**
 *
 * @param currentUser
 * @return updated user
 */
users authenticationMenu(users currentUser) {
    system("cls");

    //welcomes user depending on whether he is authenticated
    if (currentUser.authenticated == true) {
        printf("Hello %s\n", currentUser.nickname);
    } else if (currentUser.authenticated == false) {
        printf("You aren't authenticated!\n");
    }

    //whether we authenticate the user or not
    printf("\n");
    printf("Would you like to authenticate ? ");

    if (trueFalse()) {
        currentUser = authenticateUser(currentUser);
    }

    return currentUser;
}

/**
 * authenticate the user
 * @param authenticatingUser
 * @return authenticated user
 */
users authenticateUser(users authenticatingUser) {
    //setup
    system("cls");
    printf("Authenticate\n");
    printf("\n");

    //gets the username
    printf("Nickname : ");
    fflush(stdin);
    gets(authenticatingUser.nickname);

    //set user as authenticated
    authenticatingUser.authenticated = true;

    return authenticatingUser;
}