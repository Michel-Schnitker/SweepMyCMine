/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "posTest.h"
#include "boardTest.h"
#include "listTest.h"
#include "randomTest.h"
#include "gameTest.h"
#include "eventTest.h"
#include "tuiTest.h"

void runAllTests(){
    posTest();
    listTest();
    randomTest();
    boardTest();
    gameTest();
    eventTest();
    tuiTest();
}