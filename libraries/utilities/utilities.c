//
// Created by kenan.augsburger on 06.03.2020.
//

#include "utilities.h"
#include <stdio.h>

void pause(){
    //wait for input to return
    printf("\n");
    printf("press enter to return");
    fflush(stdin);
    getchar();
}