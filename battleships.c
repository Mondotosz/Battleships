/**
 * \name battleships
 * \author augsburger kenan
 * \date 04.03.2020
 * \version 0.1
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
    printf("Battleships\n");
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
                runtimeLog(INFO, "%s => gameHub()", currentUser.nickname);
                gameHub(currentUser);
                runtimeLog(INFO, "%s exit gameHub() successfully");
                break;
            case 2://Help
                runtimeLog(INFO, "%s => help()", currentUser.nickname);
                displayHelp();
                runtimeLog(INFO, "%s exit help() successfully");
                break;
            case 3://Scoreboard
                runtimeLog(INFO, "%s => scoreboard()", currentUser.nickname);
                displayScores();
                runtimeLog(INFO, "%s exit scoreboard() successfully");
                break;
            case 4://User
                runtimeLog(INFO, "%s => authentication menu()", currentUser.nickname);
                currentUser = authenticationMenu(currentUser);
                runtimeLog(INFO, "%s exit authentication menu() successfully");
                break;
            case 5://Quit
                quit = true;
                break;
            default:
                runtimeLog(ERROR, "%s unexpected selection in menu : %d", currentUser.nickname, selection);
        }

    } while (quit == false);

}

/**
 * main program
 * @return 0
 */
int main() {
    runtimeLog(INFO, "Game started");
    menu();
    runtimeLog(INFO, "Quit game correctly");
    return 0;
}
