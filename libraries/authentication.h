/**
 * this library manages user authentication
 * requires {stdio.h,stdlib.h,string.h,stdbool.h}
 */

#ifndef BATTLESHIPS_AUTHENTICATION_H
#define BATTLESHIPS_AUTHENTICATION_H

/**
 * Changes the target user
 * @param authenticatingUser
 * @return
 */
users authenticate(users authenticatingUser) {

    printf("username : ");
    fflush(stdin);
    scanf("%s", authenticatingUser.username);

    authenticatingUser.authenticated = true;

    return authenticatingUser;
}

/**
 * Shows the current user and let you authenticate
 * @param currentUser
 * @return
 */
users authenticationMenu(users currentUser) {
    char yesNo;

    system("cls");
    printf("AUTHENTICATION\n");

    if (!currentUser.authenticated) {
        printf("You aren't authenticated\n");
    } else {
        printf("Hello %s\n", currentUser.username);
    }

    printf("Would you like to? ");

    if (yesOrNo())
        currentUser = authenticate(currentUser);

    return currentUser;
}

#endif //BATTLESHIPS_AUTHENTICATION_H
