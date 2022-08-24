#ifndef POS_H_
#define POS_H_

#include "types.h"

typedef struct Pos {
    uint32_t x;
    uint32_t y;

    void (*free)(struct Pos *pos);
    void *(*clone)(struct Pos *pos);
} Pos;

Pos * createPos(uint32_t x, uint32_t y);

#endif  // POS_H_