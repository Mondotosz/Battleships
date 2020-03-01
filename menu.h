/**
 * this library contains the functions to show the menu and get the user choice
 * requires {stdio.h,stdlib.h}
 */

//TODO: find a way to use a struct in every header to get its infos and use it in menu

#ifndef BATTLESHIPS_MENU_H
#define BATTLESHIPS_MENU_H


int menu() {
    //range of choices available
    int minSelection = 1;
    int maxSelection = 6;

    //hard coded menu
    system("cls");
    printf("MENU\n");
    printf("1 - Start\n");
    printf("2 - Help\n");
    printf("3 - Scoreboard\n");
    printf("4 - Authenticate\n");
    printf("5 - Settings\n");
    printf("6 - Quit\n");

    return intSelector(minSelection, maxSelection);
}

#endif //BATTLESHIPS_MENU_H
