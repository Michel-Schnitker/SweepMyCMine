
#include "game.h"



static Board * currentBoard;

void startNewGame(uint32_t xSize, uint32_t ySize, uint32_t bombs){

    //todo: check if xSize, ySize and bombs is valid
    currentBoard = createBoard(xSize, ySize, bombs);





}

void startThisGame(Board *board){

//    nonNull(board);
    //todo: check if *board is valid
    currentBoard = board;





}

//void startZenarioGame(){} //todo: start fixed zenario with list of bomb pos.




//todo: Return of the game states

//todo: return of the current game field (concealed)
