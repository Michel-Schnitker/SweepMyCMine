#include <stdio.h>
#include <stdlib.h>

#include "board.h"


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

Board * createBoard(uint32_t xSize, uint32_t ySize, uint32_t bombs){
    Board * newBoard = calloc(1,sizeof(Board));
    nonNull(newBoard);

    newBoard->xSize = xSize;
    newBoard->ySize = ySize;
    newBoard->bombs = bombs;

    newBoard->field = createField(xSize, ySize);

    newBoard->free = freeBoard;
    newBoard->clone = cloneBoard;
    newBoard->print = printBoard;


    //todo: place Bombs ... need List.c


    return newBoard;
}

/* todo: several creators of boards are required.
 *      Constructor that does not place a bomb to a specific position.
 *      Constructor with a list of bomb locations.
 */
