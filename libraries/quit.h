/**
 * this library is used to return true and say farewell to quitting users
 * requires {stdio.h,stdlib.h,stdbool.h}
 */

#ifndef BATTLESHIPS_QUIT_H
#define BATTLESHIPS_QUIT_H

/**
 * asks for exit confirmation
 * @return true/false
 */
bool quit() {

    //exit confirmation setup
    system("cls");
    printf("Are you sure?");

    //user answer (true/false)
    return trueFalse();
}

#endif //BATTLESHIPS_QUIT_H
