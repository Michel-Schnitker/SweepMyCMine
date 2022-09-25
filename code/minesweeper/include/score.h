/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef SCORE_H_
#define SCORE_H_

#include "types.h"
#include "time.h"
#include "game.h"

//todo:

typedef struct Score {
    uint32_t rang;
    char *name;
    time_t time;
    enum GameLevel level;

    void (*free)(struct Score *score);
} ScoreEntry;

void resetScores();

bool checkIfNewRecord(enum GameLevel newLevel, time_t newTime);

ScoreEntry *getScoreEntry(enum GameLevel newLevel, uint32_t rang);

void createNewEntry(uint32_t rang, char *name, time_t time, enum GameLevel level);

void saveScores();

#endif //SCORE_H_
