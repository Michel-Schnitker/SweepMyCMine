#include "game.h"
#include "event.h"


static Board * currentBoard;

void game_startNew(uint32_t xSize, uint32_t ySize, uint32_t bombs){

    if(not checkConstructParameter(xSize, ySize, bombs)){ return;}

    //todo: check if xSize, ySize and bombs is valid
    currentBoard = constructFullyRandomBoard(xSize, ySize, bombs);





}


bool game_startThis(Board *board){
    nonNull(board);



    //todo: check if *board is valid. if not return false;

    //todo: copy board for security
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

    if(not isPosValid(currentBoard, pos)){
        print_error("Try a Move with an invalid position.");
        return false;
    }

    return true;
}

void _checkWon(){

    if(not currentBoard->gameFinish and
    currentBoard->openCells == currentBoard->bombs){
        currentBoard->gameFinish = true;
        currentBoard->gameWon = true;
    }
}

void _openCellsInArea(Pos * pos){

    if(isPosValid(currentBoard, pos)){
        currentBoard->field[pos->y][pos->x].concealed = false;
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

            if(isPosValid(currentBoard,&newPos)){

                if(currentBoard->field[y][x].bombsAround == 0 and currentBoard->field[y][x].concealed){
                    _openCellsInArea(&newPos);
                }
                else{
                    currentBoard->field[y][x].concealed = false;
                }

            }

        }
    }

}


bool game_mark(Pos * pos){
    if(not _checkBeforeMove(pos)){
        return false;
    }

    Cell *cell = &(currentBoard->field[pos->y][pos->x]);
    cell->markedAsBomb = (cell->markedAsBomb) ? false : true;
    currentBoard->bombMarkers += (cell->markedAsBomb) ? 1 : -1;

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

    cell->concealed = false;
    if(cell->containsBomb){
        currentBoard->gameFinish = true;
    }

    if(cell->bombsAround == 0){
        _openCellsInArea(pos);
    }

    _checkWon();

    return true;
}


void game_capitulation(){
    if(currentBoard == null){return;}

    currentBoard->gameFinish = true;
}


void game_print(){
    currentBoard->print(currentBoard);  //todo: debug
}


//todo: Return of the game states

//todo: return of the current game field (concealed)
