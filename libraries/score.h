//
// Created by mondotosz on 08/03/2020.
//

#ifndef BATTLESHIPS_SCORE_H
#define BATTLESHIPS_SCORE_H

#define MAX_NICKNAME_LENGTH 16
#define MAX_RECORDED_SCORES 50

typedef struct {
    char nickname[MAX_NICKNAME_LENGTH];
    int tries;
} scores;

#define SCOREBOARD "scoreboard.score"
#define SEPARATOR ';'
#define RETURN '\n'

void displayScores(void);

#endif //BATTLESHIPS_SCORE_H
