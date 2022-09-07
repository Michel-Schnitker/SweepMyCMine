/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "random.h"

static bool randomInitialized = false;

void initializeRandom(unsigned int seed){
    srand(seed);
    randomInitialized = true;
}

uint32_t getRandomInRange(uint32_t min, uint32_t max){
    assert(min <= max);

    if(not randomInitialized){ initializeRandom(time(0)); }
    return (rand() % (max - min + 1)) + min;
}