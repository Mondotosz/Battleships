/**
 * this library displays the various help files
 * requires {stdio.h,stdlib.h}
 */

//TODO: Add the help file
//TODO: Organise help in sections
//TODO: yesOrNo => numbered choice

#ifndef BATTLESHIPS_HELP_H
#define BATTLESHIPS_HELP_H

/**
 * Displays available help
 */
void helpMenu() {

    do {
        system("cls");

        printf("HELP\n");

        printf("\n");
        printf("Back?");
    } while (!yesOrNo());

}

#endif //BATTLESHIPS_HELP_H
