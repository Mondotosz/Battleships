/**
 * this library contains the functions to show the menu and get the user choice
 * requires {stdio.h,stdlib.h}
 */

//TODO:strtol?

#ifndef BATTLESHIPS_MENU_H
#define BATTLESHIPS_MENU_H

#define MAX_SELECTION 3

int menu() {
    int selection;

    system("clear");

    printf("MENU\n");
    printf("1 - Start\n");
    printf("2 - Help\n");
    printf("3 - Exit\n");

    do {
        fflush(stdin);
        scanf("%d", &selection);
    } while (selection > 0 && selection < MAX_SELECTION);

    return selection;
}

#endif //BATTLESHIPS_MENU_H
