//
// Created by mondotosz on 08/03/2020.
//

#ifndef BATTLESHIPS_SCORE_H
#define BATTLESHIPS_SCORE_H

#define MAX_NICKNAME_LENGTH 16

typedef struct {
    char nickname[MAX_NICKNAME_LENGTH];
    int tries;
} scores;

#define SCOREBOARD "scoreboard.score"
#define NICKNAME 'n'
#define SCORE 's'

void displayScores(void);

#endif //BATTLESHIPS_SCORE_H
