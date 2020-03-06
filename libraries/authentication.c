//
// Created by kenan.augsburger on 06.03.2020.
//

#include "authentication.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


users authenticationMenu(users currentUser) {
    char answer;
    system("cls");

    //To move onto utility later
    char trueChar[2] = "y";
    char falseChar[2] = "n";

    if (currentUser.authenticated == true) {
        printf("Hello %s\n", currentUser.nickname);
    } else if (currentUser.authenticated == false) {
        printf("You aren't authenticated!\n");
    }

    //whether we authenticate the user or not
    printf("Would you like to authenticate ? (y/n)\n");
    printf(": ");

    do {
        scanf("%c", &answer);
    } while (strcmp(&answer, trueChar) != 0 && strcmp(&answer, falseChar) != 0);

    if (strcmp(&answer, trueChar) == 0) {
        currentUser = authenticateUser(currentUser);
    }

    return currentUser;
}

/**
 *
 * @param authenticatingUser
 * @return authenticated user
 */
users authenticateUser(users authenticatingUser){
    //setup
    system("cls");
    printf("Authenticate\n");
    printf("\n");

    //gets the username
    printf("Nickname : ");
    fflush(stdin);
    gets(authenticatingUser.nickname);

    //set user as authenticated
    authenticatingUser.authenticated=true;

    return authenticatingUser;
}