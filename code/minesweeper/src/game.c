/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include <stdlib.h>

#include "game.h"
#include "event.h"
#include "config.h"
#include "feature.h"

static Board * currentBoard = null;
static enum GameLevel currentLevel = GAME_LEVEL_CUSTOMIZE;
static Features *features = null;

void _refreshFeatures(){
    if(features != null) free(features);
    features = getGameFeatures();
}

void game_startLevel(enum GameLevel level){

    assert(level >= 0 and level < MAX_GAME_LEVELS);


    if(currentBoard != null){
        currentBoard->free(currentBoard);
    }

    currentLevel = level;
    _refreshFeatures();

    if(level == GAME_LEVEL_CUSTOMIZE){
        if(not checkConstructParameter(features->customizeFieldConfig.xSize,
                                       features->customizeFieldConfig.ySize,
                                       features->customizeFieldConfig.bombs)){ return;}
        currentBoard = constructFullyRandomBoard(features->customizeFieldConfig.xSize,
                                                 features->customizeFieldConfig.ySize,
                                                 features->customizeFieldConfig.bombs);
    }
    else{
        if(not checkConstructParameter(GameLevelConfig[level].xSize,
                                       GameLevelConfig[level].ySize,
                                       GameLevelConfig[level].bombs)){ return;}
        currentBoard = constructFullyRandomBoard(GameLevelConfig[level].xSize,
                                                 GameLevelConfig[level].ySize,
                                                 GameLevelConfig[level].bombs);
    }

}

void game_startCustomize(uint32_t xSize, uint32_t ySize, uint32_t bombs){

    _refreshFeatures();
    features->customizeFieldConfig.xSize = xSize;
    features->customizeFieldConfig.ySize = ySize;
    features->customizeFieldConfig.bombs = bombs;
    setGameFeatures(features);

    game_startLevel(GAME_LEVEL_CUSTOMIZE);
}

void game_restart(){
    if(currentBoard != null) game_startLevel(currentLevel);
}

bool game_startThis(Board *board){
    nonNull(board);

    _refreshFeatures();

    if (features->startWithFirstSafePos){
        print_warning("Attention Game is played with FIRST_SAFE_POS. There may be a new board after the first run.");
    }

    //todo: check if *board is valid. if not return false;

    //todo: copy board for security

    if(currentBoard != null){
        currentBoard->free(currentBoard);
    }

    currentBoard = board;
    currentLevel = GAME_LEVEL_CUSTOMIZE;

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

    if(currentBoard->validPos(currentBoard, pos) and currentBoard->field[pos->y][pos->x].concealed and not currentBoard->field[pos->y][pos->x].markedAsBomb){
        currentBoard->field[pos->y][pos->x].concealed = false;
        currentBoard->openCells++;
    }

    if(currentBoard->field[pos->y][pos->x].bombsAround > 0 or currentBoard->field[pos->y][pos->x].containsBomb){
        return;
    }

    eachAround(y, pos->y){
        eachAround(x, pos->x){

            // temp Pos without function pointer
            Pos newPos = {
                    .x = x,
                    .y = y,
            };

            if(currentBoard->validPos(currentBoard,&newPos) and currentBoard->field[y][x].concealed and not currentBoard->field[pos->y][pos->x].markedAsBomb){

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


    if (features->startWithFirstSafePos){

        if(currentBoard->gameFinish or (not currentBoard->field[pos->y][pos->x].markedAsBomb and currentBoard->field[pos->y][pos->x].bombsAround != 0)){

            uint32_t x = currentBoard->xSize, y = currentBoard->ySize, bombs = currentBoard->bombs;
            currentBoard->free(currentBoard);
            currentBoard = constructRandBoardWithBombproofPos(x,
                                                              y,
                                                              bombs,
                                                              pos);

        }
    }


    time(&(currentBoard->start));
    currentBoard->gameStarted = true;
}


bool game_mark(Pos * pos){
    if(not _checkBeforeMove(pos) or features->nonFlagging){
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


void _openCompleteField(){

    for (uint32_t y = 0; y < currentBoard->ySize; ++y) {
        for (uint32_t x = 0; x < currentBoard->xSize; ++x) {
            currentBoard->field[y][x].concealed = false;
        }
    }
    currentBoard->openCells = currentBoard->ySize * currentBoard->xSize;
}

bool _allFoundAreaHelper(Pos * pos) {

    Cell *cell = &(currentBoard->field[pos->y][pos->x]);
    uint32_t countMarkers = 0;

    assert(cell->bombsAround > 0);

    eachAround(y, pos->y) {
        eachAround(x, pos->x) {

            Pos newPos = { .x = x, .y = y };

            if (currentBoard->validPos(currentBoard,&newPos) and currentBoard->field[y][x].markedAsBomb) countMarkers++;
        }
    }

    if(cell->bombsAround == countMarkers){

        eachAround(y, pos->y) {
            eachAround(x, pos->x) {

                Pos newPos = { .x = x, .y = y };

                if(currentBoard->validPos(currentBoard,&newPos) and not currentBoard->field[y][x].markedAsBomb and currentBoard->field[y][x].concealed){
                    game_open(&newPos);
                }

            }
        }
        _checkWon();
        return true;
    }

    return false;
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

        if(features->allBombsFoundAreaHelper and cell->bombsAround > 0){
            return _allFoundAreaHelper(pos);
        }
        else{
            print_warning("Trying to reopen an already open cell.");
            return false;
        }
    }

    if(cell->containsBomb){
        currentBoard->gameFinish = true;

        if (features->openFieldAfterFinish){

            _openCompleteField();
        }
        else{

            cell->concealed = false;
            currentBoard->openCells++;
        }
    }

    _checkIfFirstPos(pos);

    _openCellsInArea(pos);

    _checkWon();

    return true;
}


void game_capitulation(){
    if(currentBoard == null) return;

    if (features->openFieldAfterFinish){
        _openCompleteField();
    }

    currentBoard->gameFinish = true;
}


void destroyBoard(){
    if(currentBoard == null) return;

    nonNull(currentBoard);
    currentBoard->free(currentBoard);
    currentBoard = null;
    currentLevel = GAME_LEVEL_CUSTOMIZE;
}

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
    if(currentBoard == null){
        return null;
    }

    GameBoard *newGameBoard = calloc(1, sizeof(GameBoard));
    nonNull(newGameBoard);

    newGameBoard->xSize = currentBoard->xSize;
    newGameBoard->ySize = currentBoard->ySize;
    newGameBoard->cellsToBeFound = currentBoard->bombs - currentBoard->bombMarkers;

    newGameBoard->field = translateField();

    newGameBoard->gameStarted = currentBoard->gameStarted;
    newGameBoard->gameFinish = currentBoard->gameFinish;
    newGameBoard->gameWon = currentBoard->gameWon;

    if(currentBoard->start == 0){
        newGameBoard->runtime = 0;
    }
    else{
        time_t now;
        time(&now);
        newGameBoard->runtime = now - currentBoard->start;
        if(newGameBoard->runtime > 999) newGameBoard->runtime = 999;
    }


    newGameBoard->free = freeGameBoard;
    newGameBoard->validPos = isValidPosOnGameBoard;
    newGameBoard->gameLevel = currentLevel;

    return newGameBoard;
}

enum GameLevel getCurrentGameLevel(){

    if(currentBoard == null) currentLevel = GAME_LEVEL_CUSTOMIZE;

    return currentLevel;
}

