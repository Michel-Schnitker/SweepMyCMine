/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef EVENTTUI_H_
#define EVENTTUI_H_

#include <ncurses.h>

void drawEventWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window);

void redirectInputToEventWindow(int key);

void drawEventStatusbar(WINDOW *window, int startCol);

#endif //EVENTTUI_H_
