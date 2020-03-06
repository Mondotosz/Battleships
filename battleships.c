/**
 * \name battleships
 * \author augsburger kenan
 * \date 04.03.2020
 * \version 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "libraries/authentication.h"
#include "libraries/help.h"

#define MENU_MIN_SELECTION 1
#define MENU_MAX_SELECTION 5

void menu() {
    char string[2];
    char *pointer = NULL;
    int selection;
    bool quit = false;
    users currentUser;
    currentUser.authenticated=false;

    do {
        //display available options
        system("cls");
        printf("Battleships\n");
        printf("\n");
        printf("1 - Start\n");
        printf("2 - Help\n");
        printf("3 - Scoreboard\n");
        printf("4 - User\n");
        printf("5 - Quit\n");

        //user input
        printf("\n");
        printf(": ");

        //clean string to long
        //TODO:add as a function
        do {
            fflush(stdin);
            scanf("%s", string);
            selection = strtol(string, &pointer, MENU_MAX_SELECTION + 1);
        } while (selection < MENU_MIN_SELECTION || selection > MENU_MAX_SELECTION);

        //resulting calls
        switch (selection) {
            case 1://Start
                break;
            case 2://Help
                displayHelp();
                break;
            case 3://Scoreboard
                break;
            case 4://User
                currentUser=authenticationMenu(currentUser);
                break;
            case 5://Quit
                quit = true;
                break;
            default:
                printf("Unexpected selection : %d", selection);
                system("pause");
        }

    } while (quit == false);

}

/**
 * main program
 * @return 0
 */
int main() {
    menu();
    return 0;
}
