
#ifndef GAME_H_
#define GAME_H_

#include "types.h"
#include "board.h"
#include "pos.h"

//todo: wrap in own thread

enum CellState {
    CELL_EMPTY = 0,
    CELL_BOMB_IN_AREA_ONE = 1,
    CELL_BOMB_IN_AREA_TWO = 2,
    CELL_BOMB_IN_AREA_THREE = 3,
    CELL_BOMB_IN_AREA_FOUR = 4,
    CELL_BOMB_IN_AREA_FIVE = 5,
    CELL_BOMB_IN_AREA_SIX = 6,
    CELL_BOMB_IN_AREA_SEVEN = 7,
    CELL_BOMB_IN_AREA_EIGHT = 8,
    CELL_BOMB_INSIDE = 9,
    CELL_CONCEALED = 10,
    CELL_MARKED_AS_BOMB = 11,
};

typedef struct GameBoard {
    uint32_t xSize;
    uint32_t ySize;
    uint32_t cellsToBeFound;

    enum CellState ** field;

    bool gameStarted;
    bool gameFinish;
    bool gameWon;

    void (*free)(struct GameBoard *gameBoard);
} GameBoard;

void game_startNew(uint32_t xSize, uint32_t ySize, uint32_t bombs);

bool game_startThis(Board *board);

bool game_mark(Pos * pos);

bool game_open(Pos * pos);

void game_capitulation();

void destroyBoard();

GameBoard * getGameBoard();




#endif //GAME_H_
