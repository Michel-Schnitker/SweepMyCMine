#include <stdlib.h>

#include "pos.h"

void * clonePos(Pos *pos){
    return createPos(pos->x, pos->y);
}

void freePos(Pos *pos){
    free(pos);
}

void printPos(Pos *pos){
    UNREACHABLE;
    //todo:
}

Pos * createPos(uint32_t x, uint32_t y){
    Pos *newPos = malloc(sizeof(Pos));
    newPos->x = x;
    newPos->y = y;

    newPos->free = freePos;
    newPos->clone = clonePos;
    newPos->print = printPos;
    return newPos;
}
