/**
 * this library manages user authentication
 * requires {stdio.h,stdlib.h,string.h,stdbool.h}
 */

//currently without passwords

#ifndef BATTLESHIPS_AUTHENTICATION_H
#define BATTLESHIPS_AUTHENTICATION_H

/**
 * Changes the target user
 * @param authenticatingUser
 * @return
 */
users authenticate(users authenticatingUser) {

    //changes user's username
    printf("username : ");
    fflush(stdin);
    scanf("%s", authenticatingUser.username);

    //sets user as authenticated
    authenticatingUser.authenticated = true;

    return authenticatingUser;
}

/**
 * Shows the current user and let you authenticate
 * @param currentUser
 * @return
 */
users authenticationMenu(users currentUser) {

    //authentication menu setup
    system("cls");
    printf("AUTHENTICATION\n");

    //depending on the user status
    if (!currentUser.authenticated) {
        printf("You aren't authenticated\n");
    } else {
        printf("Hello %s\n", currentUser.username);
    }

    //authentication validation
    printf("Would you like to authenticate? ");
    if (trueFalse())
        currentUser = authenticate(currentUser);

    //returns the modified user
    return currentUser;
}

#endif //BATTLESHIPS_AUTHENTICATION_H
