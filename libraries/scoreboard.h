/**
 * this library gets the scoreboards and display them
 * requires {stdio.h,stdlib.h,string.h,stdbool.h}
 */

//TODO: working display
//TODO: read from file
//TODO: order by points
//TODO: put the file content in a struct

#ifndef BATTLESHIPS_SCOREBOARD_H
#define BATTLESHIPS_SCOREBOARD_H

#define MAX_SCORE_HISTORY 50
#define SCORE_FILE "score.history"

void displayScoreboard() {
    scores score[MAX_SCORE_HISTORY];
    FILE *scoreHistory;
    int readCursor;


    scoreHistory = fopen(SCORE_FILE, "r");

    if (scoreHistory == NULL) {
        fopen(SCORE_FILE,"w+");
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

    } while (!yesOrNo());

}

#endif //BATTLESHIPS_SCOREBOARD_H
