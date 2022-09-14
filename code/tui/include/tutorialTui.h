/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef TUTORIALTUI_H_
#define TUTORIALTUI_H_

#include <ncurses.h>

void drawTutorialWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window);

void redirectInputToTutorialWindow(int key);

void drawTutorialStatusbar(WINDOW *window, int startCol);

void openTutorialWindow();

void closeTutorialWindow();

#endif //TUTORIALTUI_H_
