#ifndef BOARD_H_
#define BOARD_H_

#include "pos.h"
#include "list.h"

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


Board * constructFullyRandomBoard(uint32_t xSize, uint32_t ySize, uint32_t bombs);

Board * constructRandBoardWithBombproofPos(uint32_t xSize, uint32_t ySize, uint32_t bombs, Pos *bombproofPos);

Board * constructBoardByListsOfPos(uint32_t xSize, uint32_t ySize, List *bombs, List *markAsBombs, List *obenCells);


#endif  // BOARD_H_
