//
// Created by mondotosz on 04/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "help.h"
#include "utilities/utilities.h"

/**
 * Displays the help info
 */
void displayHelp() {
    //displays help
    system("cls");
    printf("Help\n");
    printf("\n");
    printf("The goal of this game is to sink every boat in the grid.\n");
    printf("To do so you'll need to input coordinates to hit them.\n");
    printf("\n");
    printf("Each coordinate will be marked as such :\n");
    printf("\n");
    printf("\t%c%c=unchecked\n",176,176);
    printf("\t  =miss\n");
    printf("\t%c%c=hit\n",219,219);
    printf("\n");
    printf("Good luck on the sea young sailor!\n");

    pause();
}