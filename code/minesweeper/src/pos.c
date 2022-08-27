#include <stdlib.h>

#include "pos.h"

void * clone(Pos *pos){
    nonNull(pos);
    return createPos(pos->x, pos->y);
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

int compare(Pos *posOne, Pos *posTwo){
    return (int)(posOne->x == posTwo->x and posOne->y == posTwo->y);
}

Pos * createPos(uint32_t x, uint32_t y){
    Pos *newPos = malloc(sizeof(Pos));
    nonNull(newPos);

    newPos->x = x;
    newPos->y = y;

    newPos->free = freePos;
    newPos->clone = clone;
    newPos->print = printPos;
    newPos->compare = compare;
    return newPos;
}
