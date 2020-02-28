/**
 * \name battleships
 * \author augsburger kenan
 * \date 28.02.2020
 * \version 0.0.1
 */

//TODO: game header

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 16

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    bool authenticated;
} users;

typedef struct{
    char username[MAX_USERNAME_LENGTH];
    int score;
}scores;

#include "libraries/utilities/utilities.h"
#include "libraries/authentication.h"
#include "libraries/scoreboard.h"
#include "libraries/help.h"
#include "libraries/quit.h"
#include "menu.h"


/**
 * main program
 * @return 0
 */
int main() {
    int selection;
    bool exit = false;

    users currentUser;
    currentUser.authenticated = false;


    do {
        selection = menu();

        switch (selection) {
            case 1://start game

                break;
            case 2://displays help
                helpMenu();
                break;
            case 3://displays scoreboard
                displayScoreboard();
                break;
            case 4://authentication panel
                currentUser = authenticationMenu(currentUser);
                break;
            case 5://exit confirmation
                exit = quit();
                break;
            default:
                printf("Unexpected selection : %d\n", selection);
        }

    } while (exit == false);

    return 0;
}
