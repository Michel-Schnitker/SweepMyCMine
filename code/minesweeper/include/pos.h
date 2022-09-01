
#ifndef POS_H_
#define POS_H_

#include "types.h"

typedef struct Pos {
    int32_t x;
    int32_t y;

    void (*free)(struct Pos *pos);
    void *(*clone)(struct Pos *pos);
    void (*print)(struct Pos *pos);
    bool (*compare)(struct Pos *posOne, struct Pos *posTwo);
} Pos;

Pos * new_Pos(int32_t x, int32_t y);

void freePos(Pos *pos);

bool comparePos(Pos *posOne, Pos *posTwo);

#endif  // POS_H_
