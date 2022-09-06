#include <stdlib.h>

#include "game.h"
#include "event.h"
#include "config.h"

static Board * currentBoard = null;

void game_startNew(uint32_t xSize, uint32_t ySize, uint32_t bombs){

    if(not checkConstructParameter(xSize, ySize, bombs)){ return;}

    if(currentBoard != null){
        currentBoard->free(currentBoard);
    }

    //todo: check if xSize, ySize and bombs is valid
    currentBoard = constructFullyRandomBoard(xSize, ySize, bombs);





}


bool game_startThis(Board *board){
    nonNull(board);

#if START_WITH_FIRST_SAFE_POS
    print_warning("Attention Game is played with FIRST_SAFE_POS. There may be a new board after the first run.");
#endif


    //todo: check if *board is valid. if not return false;

    //todo: copy board for security

    if(currentBoard != null){
        currentBoard->free(currentBoard);
    }

    currentBoard = board;


    return true;


}

bool _checkBeforeMove(Pos * pos){

    if(currentBoard == null){
        print_error("Try a Move without initialized board.");
        return false;
    }

    if(currentBoard->gameFinish){
        print_error("Try a Move on a terminated board.");
        return false;
    }

    if(not currentBoard->validPos(currentBoard, pos)){
        print_error("Try a Move with an invalid position.");
        return false;
    }

    return true;
}

void _checkWon(){

    if(not currentBoard->gameFinish and
       ((currentBoard->xSize * currentBoard->ySize) - currentBoard->openCells) == currentBoard->bombs){
        currentBoard->gameFinish = true;
        currentBoard->gameWon = true;
        print_info("win a Game.");
    }
}

void _openCellsInArea(Pos * pos){

    if(currentBoard->validPos(currentBoard, pos) and currentBoard->field[pos->y][pos->x].concealed){
        currentBoard->field[pos->y][pos->x].concealed = false;
        currentBoard->openCells++;
    }

    if(currentBoard->field[pos->y][pos->x].bombsAround > 0 or currentBoard->field[pos->y][pos->x].containsBomb){
        return;
    }

    int32_t lowerX = pos->x -1, upperX = pos->x +1;
    int32_t lowerY = pos->y -1, upperY = pos->y +1;

    for (int32_t y = lowerY; y <= upperY; ++y) {
        for (int32_t x = lowerX; x <= upperX; ++x) {

            // temp Pos without function pointer
            Pos newPos = {
                    .x = x,
                    .y = y,
            };

            if(currentBoard->validPos(currentBoard,&newPos) and currentBoard->field[y][x].concealed){

                if(currentBoard->field[y][x].bombsAround == 0){
                    _openCellsInArea(&newPos);
                }
                else{
                    currentBoard->field[y][x].concealed = false;
                    currentBoard->openCells++;
                }

            }

        }
    }

}


void _checkIfFirstPos(Pos *pos){
    if(currentBoard->gameStarted){
        return;
    }
    nonNull(pos);

//    print_debug("check first pos");
#if START_WITH_FIRST_SAFE_POS
//    if(currentBoard->gameFinish or (not currentBoard->field[pos->y][pos->x].concealed and currentBoard->field[pos->y][pos->x].bombsAround != 0)){
    if(currentBoard->gameFinish or (not currentBoard->field[pos->y][pos->x].markedAsBomb and currentBoard->field[pos->y][pos->x].bombsAround != 0)){
    //if(currentBoard->gameFinish or currentBoard->field[pos->y][pos->x].bombsAround != 0){
//        print_debug("recreate board becuase of first safePos");
        uint32_t x = currentBoard->xSize, y = currentBoard->ySize, bombs = currentBoard->bombs;
        currentBoard->free(currentBoard);
        currentBoard = constructRandBoardWithBombproofPos(x,
                                                          y,
                                                          bombs,
                                                          pos);


    }
#endif

    currentBoard->gameStarted = true;
}


bool game_mark(Pos * pos){
    if(not _checkBeforeMove(pos)){
        return false;
    }

    Cell *cell = &(currentBoard->field[pos->y][pos->x]);

    if(not cell->concealed){
        print_warning("Try to mark a already open cell.");
        return false;
    }

    cell->markedAsBomb = (cell->markedAsBomb) ? false : true;
    currentBoard->bombMarkers += (cell->markedAsBomb) ? 1 : -1;
//    _checkIfFirstPos(pos);

    return true;
}





bool game_open(Pos * pos){
    if(not _checkBeforeMove(pos)){
        return false;
    }

    Cell *cell = &(currentBoard->field[pos->y][pos->x]);

    if(cell->markedAsBomb){
        print_warning("Try to open a cell marked as a bomb.");
        return false;
    }
    if(not cell->concealed){
        print_warning("Trying to reopen an already open cell.");
        return false;
    }

    if(cell->containsBomb){
        currentBoard->gameFinish = true;

#if OPEN_FIELD_AFTER_FINISH
        for (uint32_t y = 0; y < currentBoard->ySize; ++y) {
            for (uint32_t x = 0; x < currentBoard->xSize; ++x) {
                currentBoard->field[y][x].concealed = false;
            }
        }
        currentBoard->openCells = currentBoard->ySize * currentBoard->xSize;
#else
        cell->concealed = false;
        currentBoard->openCells++;
#endif
    }

    _checkIfFirstPos(pos);

    _openCellsInArea(pos);

    _checkWon();

    return true;
}


void game_capitulation(){
    if(currentBoard == null) return;

    currentBoard->gameFinish = true;
}


void destroyBoard(){
    if(currentBoard == null) return;

    nonNull(currentBoard);
    currentBoard->free(currentBoard);
    currentBoard = null;
}

//todo: Return of the game states

void freeGameBoard(GameBoard *gameBoard){
    for (uint32_t i = 0; i < gameBoard->ySize; ++i) {
        free(gameBoard->field[i]);
    }
    free(gameBoard->field);
    free(gameBoard);
}

enum CellState ** translateField(){
    enum CellState ** field = (enum CellState **) calloc(currentBoard->ySize, sizeof(enum CellState *));
    nonNull(field);

    for (uint32_t i = 0; i < currentBoard->ySize; ++i) {
        field[i] = (enum CellState *) calloc(currentBoard->xSize, sizeof(enum CellState));
    }

    for (uint32_t y = 0; y < currentBoard->ySize; ++y) {
        for (uint32_t x = 0; x < currentBoard->xSize; ++x) {

            if(currentBoard->field[y][x].markedAsBomb){

                if(not currentBoard->gameFinish or currentBoard->field[y][x].containsBomb){
                    field[y][x] = CELL_MARKED_AS_BOMB;
                }
                else{
                    field[y][x] = CELL_WRONG_MARK_AS_BOMB;
                }
                continue;
            }

            if(currentBoard->field[y][x].concealed){
                field[y][x] = CELL_CONCEALED;
                continue;
            }

            if(currentBoard->field[y][x].containsBomb){
                field[y][x] = CELL_BOMB_INSIDE;
                continue;
            }

            field[y][x] = (enum CellState) currentBoard->field[y][x].bombsAround;
        }
    }

    return field;
}

bool isValidPosOnGameBoard(Pos *pos){
    return pos->x >= 0 and
           pos->y >= 0 and
           pos->x < (int32_t) currentBoard->xSize and
           pos->y < (int32_t) currentBoard->ySize;
}

GameBoard * getGameBoard(){
    GameBoard *newGameBoard = calloc(1, sizeof(GameBoard));
    nonNull(newGameBoard);

    newGameBoard->xSize = currentBoard->xSize;
    newGameBoard->ySize = currentBoard->ySize;
    newGameBoard->cellsToBeFound = currentBoard->bombs - currentBoard->bombMarkers;

    newGameBoard->field = translateField();

    newGameBoard->gameStarted = currentBoard->gameStarted;
    newGameBoard->gameFinish = currentBoard->gameFinish;
    newGameBoard->gameWon = currentBoard->gameWon;

    newGameBoard->free = freeGameBoard;
    newGameBoard->validPos = isValidPosOnGameBoard;

    return newGameBoard;
}



