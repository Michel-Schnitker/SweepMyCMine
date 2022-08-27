
#include "game.h"



static Board * currentBoard;

void startNewGame(uint32_t xSize, uint32_t ySize, uint32_t bombs){

    //todo: check if xSize, ySize and bombs is valid
    currentBoard = constructFullyRandomBoard(xSize, ySize, bombs);





}

void startThisGame(Board *board){

//    nonNull(board);
    //todo: check if *board is valid
    currentBoard = board;





}




//todo: Return of the game states

//todo: return of the current game field (concealed)
