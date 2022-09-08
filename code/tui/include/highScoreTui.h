/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef HIGHSCORETUI_H_
#define HIGHSCORETUI_H_

#include <ncurses.h>

void drawHighScoreWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window);

void redirectInputToHighScoreWindow(int key);

void drawHighScoreStatusbar(WINDOW *window, int startCol);

#endif //HIGHSCORETUI_H_
