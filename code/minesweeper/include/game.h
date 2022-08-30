
#ifndef GAME_H_
#define GAME_H_

#include "types.h"
#include "board.h"
#include "pos.h"

//todo: wrap in own thread


void game_startNew(uint32_t xSize, uint32_t ySize, uint32_t bombs);

void game_startThis(Board *board);

void game_mark(Pos * pos);

void game_open(Pos * pos);

void game_capitulation();


//todo: Return of the game states

//todo: return of the current game field (concealed)
//todo: implement enum for field interpretation




#endif //GAME_H_
