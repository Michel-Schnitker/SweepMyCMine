
#include "posTest.h"
#include "boardTest.h"
#include "listTest.h"
#include "randomTest.h"
#include "gameTest.h"

void runAllTests(){
    posTest();
    listTest();
    randomTest();
    boardTest();
    gameTest();
}