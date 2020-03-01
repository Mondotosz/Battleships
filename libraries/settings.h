/**
 * this library displays the various settings available
 * requires {stdio.h,stdlib.h}
 */

#ifndef BATTLESHIPS_SETTINGS_H
#define BATTLESHIPS_SETTINGS_H

int settingsMenu() {
    //range of choices available
    int minSelection = 1;
    int maxSelection = 2;

    //hard coded menu
    system("cls");
    printf("Settings\n");
    printf("1 - Language\n");
    printf("2 - Back\n");

    return intSelector(minSelection,maxSelection);
}

#endif //BATTLESHIPS_SETTINGS_H
