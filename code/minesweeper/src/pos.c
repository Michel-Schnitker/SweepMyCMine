/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include <stdlib.h>

#include "random.h"
#include "pos.h"

void * clone(Pos *pos){
    nonNull(pos);
    return new_Pos(pos->x, pos->y);
}

void freePos(Pos *pos){
    nonNull(pos);
    free(pos);
}

void printPos(Pos *pos){
    nonNull(pos);

    UNREACHABLE;
    //todo:
}

bool comparePos(Pos *posOne, Pos *posTwo){
    return (posOne->x == posTwo->x and posOne->y == posTwo->y);
}

Pos * new_Pos(int32_t x, int32_t y){
    Pos *newPos = malloc(sizeof(Pos));
    nonNull(newPos);

    newPos->x = x;
    newPos->y = y;

    newPos->free = freePos;
    newPos->clone = clone;
    newPos->print = printPos;
    newPos->compare = comparePos;
    return newPos;
}

Pos *getRandomPosInRange(uint32_t minX, uint32_t maxX, uint32_t minY, uint32_t maxY){
    return new_Pos(getRandomInRange(minX,maxX), getRandomInRange(minY, maxY));
}