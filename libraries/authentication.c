//
// Created by kenan.augsburger on 06.03.2020.
//

#include "authentication.h"
#include <stdio.h>
#include <stdlib.h>

users authenticationMenu(users currentUser){

    system("cls");

    if (currentUser.authenticated==true){
        printf("you're authenticated!\n");
    }else if (currentUser.authenticated==false){
        printf("you aren't authenticated!\n");
        currentUser.authenticated=true;
    }

    //wait for input to return
    printf("\n");
    printf("press enter to return");
    fflush(stdin);
    getchar();

    return currentUser;
}
