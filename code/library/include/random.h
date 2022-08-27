
#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>

#include "types.h"


void initializeRandom(unsigned int seed);

uint32_t getRandomInRange(uint32_t min, uint32_t max);


#endif //RANDOM_H
