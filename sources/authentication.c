//
// Created by kenan.augsburger on 06.03.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities/utilities.h"
#include "utilities/logs.h"
#include "authentication.h"


/**
 *
 * @param currentUser
 * @return updated user
 */
users authenticationMenu(users currentUser) {
    runtimeLog(INFO, "entered authentication menu()");

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

    runtimeLog(INFO, "exited authentication menu()");
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
    printf("%sAuthenticate%s\n", T_BOLD, T_RESET);
    printf("\n");

    //gets the username
    printf("Nickname : ");
    fflush(stdin);
    fgets(authenticatingUser.nickname, sizeof(authenticatingUser.nickname) / sizeof(authenticatingUser.nickname[0]),
          stdin);
    authenticatingUser.nickname[strcspn(authenticatingUser.nickname, "\n")] = '\0';


    //set user as authenticated
    authenticatingUser.authenticated = true;

    runtimeLog(INFO, "authenticated as %s", authenticatingUser.nickname);

    return authenticatingUser;
}