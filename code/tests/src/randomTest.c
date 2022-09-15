/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "randomTest.h"
#include "random.h"
#include "event.h"

//todo: exchange from assert to ifPrint_Fatal

void inRangeTest(){

    print_info("    Running Tests for random in Range ...");

    uint32_t randInt = getRandomInRange(1,1);
    assert(randInt == 1);

    randInt = getRandomInRange(0,2);
    assert(randInt == 0 or randInt == 1 || randInt == 2);

    print_success("         Passed");
}

void posInRangeTest(){

    print_info("    Running Tests for random Pos in Range ...");

    Pos *randomPos = getRandomPosInRange(3,4,7,8);

    assert(randomPos->x == 3 or randomPos->x == 4);
    assert(randomPos->y == 7 or randomPos->y == 8);

    randomPos->free(randomPos);

    print_success("         Passed");
}

void randomTest(){

    print_info("Running Tests for random.c");

    inRangeTest();
    posInRangeTest();
}