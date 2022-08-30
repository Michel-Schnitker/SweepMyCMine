#include "game.h"



static Board * currentBoard;

void game_startNew(uint32_t xSize, uint32_t ySize, uint32_t bombs){

    if(not checkConstructParameter(xSize, ySize, bombs)){ return;}

    //todo: check if xSize, ySize and bombs is valid
    currentBoard = constructFullyRandomBoard(xSize, ySize, bombs);





}


void game_startThis(Board *board){
    nonNull(board);

    //todo: check if *board is valid
    currentBoard = board;





}


void game_mark(Pos * pos){
    if(currentBoard == null or
    currentBoard->gameFinish or
    not isPosValid(currentBoard, pos)){
        return;
    }


}


void game_open(Pos * pos){
    if(currentBoard == null){return;}


}


void game_capitulation(){
    if(currentBoard == null){return;}


}



//todo: Return of the game states

//todo: return of the current game field (concealed)
