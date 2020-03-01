/**
 * this library let you chose the display language
 * requires {stdio.h,stdlib.h}
 */

#ifndef BATTLESHIPS_LANGUAGE_H
#define BATTLESHIPS_LANGUAGE_H

void changeLanguage() {



    //hard coded menu
    system("cls");
    printf("LANGUAGE\n");
    printf("1 - English\n");
    printf("2 - Francais\n");
    printf("3 - Back\n");

    switch (intSelector(1, 3)) {
        case 1:
            if (!languageFileCheck(en))
                displayLang = en;
            break;
        case 2:
            if (!languageFileCheck(fr))
                displayLang = fr;
            break;
        case 3:

            break;
        default:
            printf("Unexpected selection");
    }

}

#endif //BATTLESHIPS_LANGUAGE_H
