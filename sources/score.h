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

typedef struct {
    scores existingScores[MAX_RECORDED_SCORES];
    int range;
} scoreboard;

void displayScores(void);

#define SCOREBOARD_JSON "scoreboard.json"
#define NICKNAME 'n'
#define TRIES 't'

scoreboard getScoreboard();

void newScore(scores newScore);

#endif //BATTLESHIPS_SCORE_H
