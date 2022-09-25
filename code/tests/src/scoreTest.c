/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "scoreTest.h"
#include "score.h"
#include "event.h"
#include "game.h"

void getScore(){

    print_info("    Running Tests for create and delete a new Score ...");

    ScoreEntry *score = getScoreEntry(GAME_LEVEL_BEGINNER, 1);
    ifPrint_fatal(score->name != null, "         Name is not NULL after resetting Scores");
    score->free(score);

    print_success("         Passed");
}

void scoreTest(){

    print_info("Running Tests for score.c");

    resetScores();

    getScore();

    resetScores();
}
