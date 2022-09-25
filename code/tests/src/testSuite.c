/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "event.h"

#include "posTest.h"
#include "boardTest.h"
#include "listTest.h"
#include "randomTest.h"
#include "gameTest.h"
#include "featuresTest.h"
#include "scoreTest.h"
#include "eventTest.h"
#include "tuiTest.h"

void runAllTests(){

    startEventLogging(DIREKT_PRINT);

    // Test for standalone library
    randomTest();
    listTest();
    eventTest();

    // Test for Minesweeper library
    posTest();
    boardTest();
    gameTest();
    featuresTest();
    scoreTest();

    // Test for Frameworks
    tuiTest();

    stopEventLogging();
}
