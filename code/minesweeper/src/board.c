#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "random.h"


void printBoard(Board *board){

    printf("\n");
    for (uint32_t y = 0; y < board->ySize; ++y) {
        for (uint32_t x = 0; x < board->xSize; ++x) {
            printf("%i  ",board->field[y][x].testCounter);
        }
        printf("\n");
    }
    printf("\n");

}

void freeBoard(Board *board){

    for (uint32_t i = 0; i < board->ySize; ++i) {
        free(board->field[i]);
    }
    free(board->field);
    free(board);
}

void * cloneBoard(Board *board){
    UNREACHABLE;
    //todo:
}

Cell ** createField(uint32_t xSize, uint32_t ySize){
    Cell ** newField = (Cell **) calloc(ySize, sizeof(Cell*));
    nonNull(newField);
    for (uint32_t i = 0; i < ySize; ++i) {
        newField[i] = (Cell *) calloc(xSize, sizeof(Cell));
    }

    for (uint32_t y = 0; y < ySize; ++y) {
        for (uint32_t x = 0; x < xSize; ++x) {
            newField[y][x].testCounter = y+x*100;
            //todo: init real Cell
        }
    }

    return newField;
}

void placeBombOnPos(Board * newBoard, Pos * bombPos){
    //todo: place Bomb and increment Area

    UNREACHABLE;

    newBoard->field[bombPos->y][bombPos->x].containsBomb = true;

    //todo: increment Area
}


void placeRandomBombs(Board * newBoard, uint32_t bombs, Pos * bombproofPos){
    nonNull(newBoard);
    assert(bombs > 0);

    List *places = createList();
    Pos * currentPos;

    for (uint32_t y = 0; y < newBoard->ySize; ++y) {
        for (uint32_t x = 0; x < newBoard->xSize; ++x) {
            currentPos = createPos(x,y);
            places->add(places, currentPos);
        }
    }

    if(bombproofPos != null){
        places->remove(places,bombproofPos,bombproofPos->compare,bombproofPos->free);
    }

    while (bombs > 0){
        currentPos = places->popIndex(places, getRandomInRange(0, bombs--));

        placeBombOnPos(newBoard, currentPos);
        currentPos->free(currentPos);

        newBoard->bombs++;
    }

    //todo: including the free function via the "object" is not that pretty
    places->delete(places, free);
}

Board * createBoard(uint32_t xSize, uint32_t ySize){
    Board * newBoard = calloc(1,sizeof(Board));
    nonNull(newBoard);

    newBoard->xSize = xSize;
    newBoard->ySize = ySize;

    newBoard->field = createField(xSize, ySize);

    newBoard->free = freeBoard;
    newBoard->clone = cloneBoard;
    newBoard->print = printBoard;

    return newBoard;
}


Board * constructFullyRandomBoard(uint32_t xSize, uint32_t ySize, uint32_t bombs){
    Board * newBoard = createBoard(xSize, ySize);
    placeRandomBombs(newBoard, bombs, null);
    return newBoard;
}

Board * constructRandBoardWithBombproofPos(uint32_t xSize, uint32_t ySize, uint32_t bombs, Pos *bombproofPos){
    Board * newBoard = createBoard(xSize, ySize);

    //todo:

    return newBoard;
}

Board * constructBoardByListsOfPos(uint32_t xSize, uint32_t ySize, List *bombs, List *markAsBombs, List *obenCells){
    Board * newBoard = createBoard(xSize, ySize);

    //todo:

    return newBoard;
}


