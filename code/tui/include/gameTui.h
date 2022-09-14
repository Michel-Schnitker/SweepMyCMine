/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef GAMETUI_H_
#define GAMETUI_H_

#include <ncurses.h>

void drawGameWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *gameWindow);

void redirectInputToGameWindow(int key);

void drawGameStatusbar(WINDOW *window, int startCol);

void openGameWindow();

void closeGameWindow();

#endif //GAMETUI_H_
