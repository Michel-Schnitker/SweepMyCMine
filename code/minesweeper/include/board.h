
#ifndef BOARD_H_
#define BOARD_H_


#include "types.h"
#include "pos.h"
#include "list.h"

typedef struct Cell {
    bool concealed;
    bool markedAsBomb;
    bool containsBomb;
    uint32_t bombsAround;
} Cell;

typedef struct Board {
    uint32_t xSize;
    uint32_t ySize;
    uint32_t bombs;

    Cell ** field;

    uint32_t openCells;
    uint32_t bombMarkers;
    bool gameStarted;
    bool gameFinish;
    bool gameWon;

    void (*free)(struct Board *board);
    void (*print)(struct Board *board);
    bool (*validPos)(struct Board *board, struct Pos *pos);
} Board;

bool checkConstructParameter(uint32_t xSize, uint32_t ySize, uint32_t bombs);

Board * constructFullyRandomBoard(uint32_t xSize, uint32_t ySize, uint32_t bombs);

Board * constructRandBoardWithBombproofPos(uint32_t xSize, uint32_t ySize, uint32_t bombs, Pos *bombproofPos);

Board * constructBoardByListsOfPos(uint32_t xSize, uint32_t ySize, List *bombs);



#endif  //BOARD_H_
