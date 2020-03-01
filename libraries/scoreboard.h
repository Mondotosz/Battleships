/**
 * this library gets the scoreboards and display them
 * requires {stdio.h,stdlib.h,string.h,stdbool.h}
 */

//TODO: working display
//TODO: read from file
//TODO: order by points
//TODO: put the file content in a struct
//TODO:WTF FIX THIS SHIT

#ifndef BATTLESHIPS_SCOREBOARD_H
#define BATTLESHIPS_SCOREBOARD_H

#define MAX_SCORE_HISTORY 50

void displayScoreboard() {
    scores score[MAX_SCORE_HISTORY];
    filePath path={"./assets/scores",".history"};
    FILE *scoreHistory;
    int readCursor;
    char scorePath[MAX_PATH_LENGTH];

    strcpy(scorePath,path.path);
    strcat(scorePath,"/score");
    strcat(scorePath,path.extension);

    //setup
    system("cls");
    printf("SCOREBOARD\n");

    //score reading
    scoreHistory = fopen(scorePath, "r");

    if (scoreHistory == NULL) {
        fopen(scorePath,"w+");
    }

    for (int j = 0; j < MAX_SCORE_HISTORY; ++j) {
        readCursor = fgetc(scoreHistory);
        if (feof(scoreHistory))
            break;
        printf("%c",readCursor);

    }
    fclose(scoreHistory);

    printf("\n");

    do {
        /**
        system("cls");
        printf("SCOREBOARD\n");
        printf("\n");

        for (int i = 0; i < sizeof(score) / sizeof(score[0]); ++i) {
            printf("%d - %s \t%d \tpoints\n", i + 1, score[i].username, score[i].score);
        }
        */

        printf("\n");
        printf("Back?");

    } while (!trueFalse());

}

#endif //BATTLESHIPS_SCOREBOARD_H
