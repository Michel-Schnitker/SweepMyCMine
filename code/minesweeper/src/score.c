/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "score.h"
#include <stdlib.h>
#include "string.h"

static ScoreEntry **scores = null;

void free_ScoreEntry(ScoreEntry *entry){
    if(entry->name != null) free(entry->name);
    free(entry);
}

void _wirteEmptyScores(){
    for (uint32_t level = 0; level < MAX_GAME_LEVELS; ++level) {
        for (uint32_t rang = 0; rang < SCORE_NUMBER_SCORES_TO_SAVED; ++rang) {

            ScoreEntry *score = &(scores[level][rang]);

            score->rang = rang+1;
            score->level = level;
            if(score->name != null){
                free(score->name);
                score->name = null;
            }
            score->time = 0;
        }
    }
}

void _initScores(){
    scores = (ScoreEntry **) calloc(MAX_GAME_LEVELS, sizeof(ScoreEntry*));
    nonNull(scores);
    for (uint32_t i = 0; i < MAX_GAME_LEVELS; ++i) {
        scores[i] = (ScoreEntry *) calloc(SCORE_NUMBER_SCORES_TO_SAVED, sizeof(ScoreEntry));
    }

    _wirteEmptyScores();
}

void resetScores(){
    if(scores == null) {
        _initScores();
    }
    else{
        _wirteEmptyScores();
    }
}

void _loadScores(){
    _initScores();

    //todo: load from Disk
}

bool checkIfNewRecord(enum GameLevel newLevel, time_t newTime){

    assert(newLevel > 0 and newLevel < MAX_GAME_LEVELS);

    ScoreEntry *lastEntry = &(scores[newLevel][SCORE_NUMBER_SCORES_TO_SAVED - 1]);
    return lastEntry->time > newTime or lastEntry->name == null;
}

ScoreEntry *getScoreEntry(enum GameLevel newLevel, uint32_t rang){

    assert(rang >= 1 and rang <= SCORE_NUMBER_SCORES_TO_SAVED);
    assert(newLevel > 0 and newLevel < MAX_GAME_LEVELS);

    rang--;

    if(scores == null) _loadScores();

    ScoreEntry *newScore = calloc(1,sizeof(ScoreEntry));
    newScore->free = free_ScoreEntry;
    newScore->rang = rang+1;
    newScore->time = scores[newLevel][rang].time;
    newScore->level = newLevel;

    if(scores[newLevel][rang].name == null){
        newScore->name = null;
    }
    else{
        char *name = malloc((strlen(scores[newLevel][rang].name) + 1)* sizeof(char));
        strcpy(name, scores[newLevel][rang].name);
        newScore->name = name;
    }

    return newScore;
}

void createNewEntry(uint32_t rang, char *name, time_t time, enum GameLevel level){

    if ( not checkIfNewRecord(level, time)) return;

    (void) rang;
    (void) name;
    //todo: Sort into array
}

void saveScores(){
    //todo: save to disk
}
