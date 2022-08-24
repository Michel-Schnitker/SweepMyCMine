#ifndef BOARD_H_
#define BOARD_H_

#include "types.h"

typedef struct Cell {
    bool concealed;
    bool markedAsBomb;
    bool containsBomb;
    uint32_t bombsAround;

    uint32_t testCounter;   //todo: delete
} Cell;

typedef struct Board {
    uint32_t xSize;
    uint32_t ySize;
    uint32_t bombs;

    Cell ** field;

    bool gameFinish;
    bool gameWon;

    void (*free)(struct Board *board);
    void *(*clone)(struct Board *board);
    void (*print)(struct Board *board);
} Board;


Board * createBoard(uint32_t xSize, uint32_t ySize, uint32_t bombs);


#endif  // BOARD_H_
