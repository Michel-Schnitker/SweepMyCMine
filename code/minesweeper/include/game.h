#ifndef GAME_H_
#define GAME_H_

#include "types.h"
#include "board.h"
#include "pos.h"

//todo: wrap in own thread


void startNewGame(uint32_t xSize, uint32_t ySize, uint32_t bombs);

void startThisGame(Board *board);

//void startZenarioGame(); //todo: start fixed zenario with list of bomb pos.

void markAsBomb(Pos * pos);

void obenCell(Pos * pos);

void gameCapitulation();


//todo: Return of the game states

//todo: return of the current game field (concealed)
//todo: implement enum for field interpretation



#endif  // GAME_H_
