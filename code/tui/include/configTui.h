/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef CONFIGTUI_H_
#define CONFIGTUI_H_

#include <ncurses.h>

void drawConfigWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window);

void redirectInputToConfigWindow(int key);

void drawConfigStatusbar(WINDOW *window, int startCol);

#endif //CONFIGTUI_H_
