/**
 * \name battleships
 * \author augsburger kenan
 * \date 28.02.2020
 * \version 0.0.1
 */

//TODO: game header

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <errno.h>
#include <dirent.h>

#define MAX_USERNAME_LENGTH 16
#define MAX_ACRONYM_LENGTH 4
#define MAX_LANG_NAME_LENGTH 16
#define MAX_PATH_LENGTH 64
#define MAX_EXTENSION_LENGTH 16
#define MAX_TITLE_LENGTH 32
#define MAX_CONTENT_LENGTH 1024
#define MAX_FOOTER_LENGTH 32

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    bool authenticated;
} users;

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    int score;
} scores;

typedef struct {
    int id;
    char acronym[MAX_ACRONYM_LENGTH];
    char name[MAX_LANG_NAME_LENGTH];
    char trueString[5];
    char falseString[5];
} language;

typedef struct {
    char path[MAX_PATH_LENGTH];
    char extension[MAX_EXTENSION_LENGTH];
} filePath;

typedef struct {
    char title[MAX_TITLE_LENGTH];
    char content[MAX_CONTENT_LENGTH];
    char footer[MAX_FOOTER_LENGTH];
}displayLayout;

//global variables

const language en = {1, "en", "english", "y", "n"};
const language fr = {2, "fr", "francais", "o", "n"};

//native display language
language displayLang;


const filePath languagesPath[] = {
        {"./assets/languages", ".menu"},
        {"./assets/languages", ".game"},
        {"./assets/languages", ".help"},
        {"./assets/languages", ".scoreboard"},
        {"./assets/languages", ".scoreboard"},
        {"./assets/languages", ".auth"},
        {"./assets/languages", ".auth"},
        {"./assets/languages", ".settings"},
        {"./assets/languages", ".lang"},
        {"./assets/languages", ".quit"},
};

#include "libraries/utilities/utilities.h"
#include "libraries/settings/language.h"
#include "libraries/authentication.h"
#include "libraries/scoreboard.h"
#include "libraries/help.h"
#include "libraries/quit.h"
#include "libraries/settings.h"
#include "menu.h"


/**
 * main program
 * @return 0
 */
int main() {
    int selection, settingsSelection;
    bool exit = false;

    //initialize default language
    displayLang = en;

    //launch as unauthenticated user
    users currentUser;
    currentUser.authenticated = false;

    exit = dirCheck();
    if (!exit)
        exit = languageFileCheck(en);

    while (exit == false) {
        selection = menu();

        switch (selection) {
            case 1://start game

                break;
            case 2://displays help
                helpMenu();
                break;
            case 3://displays scoreboard
                displayScoreboard();
                break;
            case 4://authentication panel
                currentUser = authenticationMenu(currentUser);
                break;
            case 5:
                settingsSelection = settingsMenu();

                switch (settingsSelection) {
                    case 1://Language
                        changeLanguage();
                        break;
                    case 2://Back
                        break;
                    default:
                        printf("Unexpected selection %d\n", settingsSelection);
                }

                break;
            case 6://exit confirmation
                exit = quit();
                break;
            default:
                printf("Unexpected selection : %d\n", selection);
        }

    }

    return 0;
}
