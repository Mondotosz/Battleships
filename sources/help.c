//
// Created by mondotosz on 04/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "help.h"
#include "utilities/utilities.h"
#include "utilities/logs.h"

/**
 * Displays the help info
 */
void displayHelp() {
    const int offset = 4;
    runtimeLog(INFO, "entered help()");
    //displays help
    system("cls");
    printf("%sHelp%s\n", T_BOLD, T_RESET);
    printf("\n");
    printf("The goal of this game is to sink every boat in the grid.\n");
    printf("To do so you'll need to input coordinates to hit them.\n");
    printf("\n");
    printf("Each coordinate will be marked as such :\n");
    printf("\n");
    printf("%*s  =unchecked\n", offset, "");
    printf("%*s%s%c%c%s=miss\n", offset, "", T_CYAN, 176, 176, T_RESET);
    printf("%*s%s%c%c%s=hit\n", offset, "", T_RED, 219, 219, T_RESET);
    printf("\n");
    printf("Good luck on the sea young sailor!\n");

    pause();
    runtimeLog(INFO, "exited help()");
}