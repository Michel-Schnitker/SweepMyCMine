
#ifndef GAMETUI_H_
#define GAMETUI_H_

#include <ncurses.h>

void drawGameWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *gameWindow);

void initNewGame();

void redirectInputToGameWindow(int key);

void drawGameStatusbar(WINDOW *window, int startCol);


#endif //GAMETUI_H_
