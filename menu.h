/**
 * this library contains the functions to show the menu and get the user choice
 * requires {stdio.h,stdlib.h}
 */

//TODO: find a way to use a struct in every header to get its infos and use it in menu

#ifndef BATTLESHIPS_MENU_H
#define BATTLESHIPS_MENU_H

//range of choices available
#define MIN_SELECTION 1
#define MAX_SELECTION 5

int menu() {

    //hard coded menu
    system("cls");
    printf("MENU\n");
    printf("1 - Start\n");
    printf("2 - Help\n");
    printf("3 - Scoreboard\n");
    printf("4 - Authenticate\n");
    printf("5 - Quit\n");

    return intSelector(MIN_SELECTION,MAX_SELECTION);
}

#endif //BATTLESHIPS_MENU_H
