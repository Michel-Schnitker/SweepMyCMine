/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "board.h"
#include "random.h"
#include "event.h"

void printBoard(Board *board){

    printf("\n");
    for (uint32_t y = 0; y < board->ySize; ++y) {
        for (uint32_t x = 0; x < board->xSize; ++x) {

            if(board->field[y][x].markedAsBomb){
                printf("%s  ", BOARD_SIGN_MARKASBOMB);
            }
            else{
#if not DEBUGMODE
                if(board->field[y][x].concealed){
                    printf("%s  ", BOARD_SIGN_CONCEALED);
                }
                else
#endif
                if(board->field[y][x].containsBomb){
                    printf("%s  ", BOARD_SIGN_BOMB);
                }
                else{
                    printf("%i  ",board->field[y][x].bombsAround);
                }
            }

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

Cell ** createField(uint32_t xSize, uint32_t ySize){
    Cell ** newField = (Cell **) calloc(ySize, sizeof(Cell*));
    nonNull(newField);
    for (uint32_t i = 0; i < ySize; ++i) {
        newField[i] = (Cell *) calloc(xSize, sizeof(Cell));
    }

    for (uint32_t y = 0; y < ySize; ++y) {
        for (uint32_t x = 0; x < xSize; ++x) {
//            newField[y][x].bombsAround = 0;
            newField[y][x].concealed = true;
//            newField[y][x].markedAsBomb = false;
//            newField[y][x].containsBomb = false;
        }
    }

    return newField;
}

bool _isPosValid(Board * board, int32_t x, int32_t y){
    return x >= 0 and
           y >= 0 and
           x < (int32_t) board->xSize and
           y < (int32_t) board->ySize;
}

bool isPosValid(Board * board, Pos *pos){
    return _isPosValid(board, pos->x, pos->y);
}

void placeBombOnPos(Board * newBoard, Pos * bombPos){
    assert(isPosValid(newBoard, bombPos));

    int32_t lowerX = bombPos->x -1, upperX = bombPos->x +1;
    int32_t lowerY = bombPos->y -1, upperY = bombPos->y +1;

    for (int32_t y = lowerY; y <= upperY; ++y) {
        for (int32_t x = lowerX; x <= upperX; ++x) {

            if(_isPosValid(newBoard, x, y)){
                newBoard->field[y][x].bombsAround++;
            }
        }
    }

    newBoard->field[bombPos->y][bombPos->x].containsBomb = true;
    newBoard->bombs++;
}


void placeRandomBombs(Board * newBoard, uint32_t bombs, Pos * bombproofPos){
    nonNull(newBoard);

    List *places = new_List();
    Pos * currentPos;

    for (uint32_t y = 0; y < newBoard->ySize; ++y) {
        for (uint32_t x = 0; x < newBoard->xSize; ++x) {
            currentPos = new_Pos(x,y);
            places->add(places, currentPos);
        }
    }

    if(bombproofPos != null){

        int32_t lowerX = bombproofPos->x -1, upperX = bombproofPos->x +1;
        int32_t lowerY = bombproofPos->y -1, upperY = bombproofPos->y +1;

        for (int32_t y = lowerY; y <= upperY; ++y) {
            for (int32_t x = lowerX; x <= upperX; ++x) {

                if(_isPosValid(newBoard, x, y)){

                    Pos newPos = {.x = x, .y = y};

                    places->remove(places,&newPos,(void*)(void*) comparePos,(void*)(void*) freePos);
                }
            }
        }

    }

    assert(bombs < places->size);

    while (bombs-- > 0){
        currentPos = places->popIndex(places, getRandomInRange(0, places->size -1));

        placeBombOnPos(newBoard, currentPos);
        currentPos->free(currentPos);
    }

    //todo: including the free function via the "object" is not that pretty
    places->delete(places, (void*)freePos);
}

Board * createBoard(uint32_t xSize, uint32_t ySize){
    Board * newBoard = calloc(1,sizeof(Board));
    nonNull(newBoard);

    newBoard->xSize = xSize;
    newBoard->ySize = ySize;

    newBoard->field = createField(xSize, ySize);

    newBoard->free = freeBoard;
    newBoard->print = printBoard;
    newBoard->validPos = isPosValid;

    return newBoard;
}

bool checkConstructParameter(uint32_t xSize, uint32_t ySize, uint32_t bombs){

    return(xSize >= BOARD_MINSIZE_X and ySize >= BOARD_MINSIZE_Y and
            xSize <= BOARD_MAXSIZE_X and ySize <= BOARD_MAXSIZE_Y and
#if START_WITH_FIRST_SAFE_POS
            bombs + 9 < xSize * ySize and
#else
            bombs < xSize * ySize and
#endif
            bombs > 0
    );
}

Board * constructFullyRandomBoard(uint32_t xSize, uint32_t ySize, uint32_t bombs){
    assert(checkConstructParameter(xSize, ySize, bombs));

    Board * newBoard = createBoard(xSize, ySize);
    placeRandomBombs(newBoard, bombs, null);
    return newBoard;
}

Board * constructRandBoardWithBombproofPos(uint32_t xSize, uint32_t ySize, uint32_t bombs, Pos *bombproofPos){
    assert(checkConstructParameter(xSize, ySize, bombs));

    Board * newBoard = createBoard(xSize, ySize);
    placeRandomBombs(newBoard, bombs, bombproofPos);
    return newBoard;
}

Board * constructBoardByListsOfPos(uint32_t xSize, uint32_t ySize, List *bombs){
    assert(checkConstructParameter(xSize, ySize, bombs->size));

    Board * newBoard = createBoard(xSize, ySize);

    for (uint32_t i = 0; i < bombs->size; ++i) {
        Pos *bomb = bombs->getIndex(bombs, i);
        placeBombOnPos(newBoard, bomb);
    }

    return newBoard;
}


