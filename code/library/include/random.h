/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "pos.h"

void initializeRandom(unsigned int seed);

uint32_t getRandomInRange(uint32_t min, uint32_t max);

#endif //RANDOM_H_
