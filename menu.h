/**
 * this library contains the functions to show the menu and get the user choice
 * requires {stdio.h,stdlib.h}
 */

//TODO: find a way to use a struct in every header to get its infos and use it in menu

#ifndef BATTLESHIPS_MENU_H
#define BATTLESHIPS_MENU_H

//number of choices available
#define MAX_SELECTION 5

int menu() {
    char str[2];
    char *ptr = NULL;
    int selection;

    //hard coded menu
    system("cls");
    printf("MENU\n");
    printf("1 - Start\n");
    printf("2 - Help\n");
    printf("3 - Scoreboard\n");
    printf("4 - Authenticate\n");
    printf("5 - Quit\n");

    do {
        fflush(stdin);
        scanf("%s", str);
        selection = strtol(str, &ptr, MAX_SELECTION + 1);
    } while (selection < 1 || selection > MAX_SELECTION);

    return selection;
}

#endif //BATTLESHIPS_MENU_H
