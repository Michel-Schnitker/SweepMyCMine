
#include "posTest.h"
#include "boardTest.h"
#include "listTest.h"
#include "randomTest.h"
#include "gameTest.h"
#include "tuiTest.h"

void runAllTests(){
    posTest();
    listTest();
    randomTest();
    boardTest();
    gameTest();
    tuiTest();
}