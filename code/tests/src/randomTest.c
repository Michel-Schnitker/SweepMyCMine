/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "randomTest.h"
#include "random.h"
#include "event.h"

void inRangeTest(){

    print_info("    Running Tests for random in Range ...");

    uint32_t randInt = getRandomInRange(1,1);
    ifPrint_fatal(randInt != 1, "         Random int is not in range from 1 to 1.");

    randInt = getRandomInRange(0,2);
    ifPrint_fatal(randInt != 0 and randInt != 1 and randInt != 2 , "         Random int is not in range from 0 to 2.");

    print_success("         Passed");
}

void randomTest(){

    print_info("Running Tests for random.c");

    inRangeTest();
}
