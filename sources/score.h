//
// Created by mondotosz on 08/03/2020.
//

#ifndef BATTLESHIPS_SCORE_H
#define BATTLESHIPS_SCORE_H

#define MAX_NICKNAME_LENGTH 16
#define MAX_RECORDED_SCORES 50

typedef struct {
    char nickname[MAX_NICKNAME_LENGTH];
    int misses;
} scores;

typedef struct {
    scores existingScores[MAX_RECORDED_SCORES];
    int range;
} scoreboard;

void displayScores(void);

#define SCOREBOARD_JSON "scoreboard.json"
#define NICKNAME 'n'
#define TRIES 'm'

scoreboard getScoreboard();

void newScore(scores newScore);

scoreboard bubbleSortScoreboard(scoreboard unsortedScoreboard);

#endif //BATTLESHIPS_SCORE_H
