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

bool _isPosValid(Board * board, uint32_t x, uint32_t y){
    return x >= 0 and
           y >= 0 and
           x < board->xSize and
           y < board->ySize;
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
        places->remove(places,bombproofPos,(void*)(void*)bombproofPos->compare,(void*)(void*)bombproofPos->free);
    }

    while (bombs-- > 0){
        currentPos = places->popIndex(places, getRandomInRange(0, places->size -1));

        placeBombOnPos(newBoard, currentPos);
        currentPos->free(currentPos);
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
    newBoard->print = printBoard;

    return newBoard;
}

void checkConstructParameter(uint32_t xSize, uint32_t ySize, uint32_t bombs){
    assert(xSize >= BOARD_MINSIZE_X and ySize >= BOARD_MINSIZE_Y);
    assert(xSize <= BOARD_MAXSIZE_X and ySize <= BOARD_MAXSIZE_Y);
    assert(bombs < xSize * ySize);
    assert(bombs > 0);
}

Board * constructFullyRandomBoard(uint32_t xSize, uint32_t ySize, uint32_t bombs){
    checkConstructParameter(xSize, ySize, bombs);

    Board * newBoard = createBoard(xSize, ySize);
    placeRandomBombs(newBoard, bombs, null);
    return newBoard;
}

Board * constructRandBoardWithBombproofPos(uint32_t xSize, uint32_t ySize, uint32_t bombs, Pos *bombproofPos){
    checkConstructParameter(xSize, ySize, bombs);

    Board * newBoard = createBoard(xSize, ySize);
    placeRandomBombs(newBoard, bombs, bombproofPos);
    return newBoard;
}

Board * constructBoardByListsOfPos(uint32_t xSize, uint32_t ySize, List *bombs){
    checkConstructParameter(xSize, ySize, bombs->size);

    Board * newBoard = createBoard(xSize, ySize);

    for (uint32_t i = 0; i < bombs->size; ++i) {
        Pos *bomb = bombs->getIndex(bombs, i);
        placeBombOnPos(newBoard, bomb);
    }

    return newBoard;
}


