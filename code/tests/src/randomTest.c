
#include "randomTest.h"
#include "random.h"
#include "event.h"


void inRangeTest(){

    print_info("    Running Tests for random in Range ...");

    uint32_t randInt = getRandomInRange(1,1);
    assert(randInt == 1);

    randInt = getRandomInRange(0,2);
    assert(randInt == 0 or randInt == 1 || randInt == 2);

    print_success("         Passed");
}

void randomTest(){

    print_info("Running Tests for random.c");

    inRangeTest();
}