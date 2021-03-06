/**
 * \name battleships
 * \author augsburger kenan
 * \date 5.04.2020
 * \version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sources/utilities/logs.h"
#include "sources/utilities/utilities.h"
#include "sources/authentication.h"
#include "sources/score.h"
#include "sources/help.h"
#include "sources/game.h"

#define MENU_MIN_SELECTION 1
#define MENU_MAX_SELECTION 5

/**
 * displays the menu
 */
void displayMenu() {
    //display available options
    system("cls");
    printf("%sBattleships%s\n", T_BOLD, T_RESET);
    printf("\n");
    printf("1 - Start\n");
    printf("2 - Help\n");
    printf("3 - Scoreboard\n");
    printf("4 - User\n");
    printf("5 - Quit\n");
}

/**
 * calls the various functions depending on the user
 */
void menu() {
    int selection;
    bool quit = false;
    users currentUser;
    runtimeLog(INFO, "entered menu()");

    //default user
    strncpy(currentUser.nickname, "User", MAX_NICKNAME_LENGTH);
    currentUser.authenticated = false;

    do {

        displayMenu();
        printf("\n");
        selection = getInt(MENU_MIN_SELECTION, MENU_MAX_SELECTION);

        //resulting calls
        switch (selection) {
            case 1://Start
                gameHub(currentUser);
                break;
            case 2://Help
                displayHelp();
                break;
            case 3://Scoreboard
                displayScores();
                break;
            case 4://User
                currentUser = authenticationMenu(currentUser);
                break;
            case 5://Quit
                quit = true;
                break;
            default:
                runtimeLog(ERROR, "unexpected selection in menu : %d", selection);
        }

    } while (quit == false);
    runtimeLog(INFO, "exited menu()");
}

/**
 * main program
 * @return 0
 */
int main() {
    runtimeLog(INFO, "Program start");
    menu();
    runtimeLog(INFO, "Program end");
    return 0;
}
