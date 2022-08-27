#include "randomTest.h"
#include "random.h"

void inRangeTest(){

    //todo: add log message

    uint32_t randInt = getRandomInRange(1,1);
    assert(randInt == 1);

    randInt = getRandomInRange(0,2);
    assert(randInt == 0 or randInt == 1 || randInt == 2);
}

void randomTest(){

    //todo: add log message

    inRangeTest();
}