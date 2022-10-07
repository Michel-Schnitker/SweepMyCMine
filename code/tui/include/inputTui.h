/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef INPUTTUI_H_
#define INPUTTUI_H_

#include "ncurses.h"

WINDOW* drawInputWindow(int startCol, int startRow, char *reqString);

void deleteInputWindow(WINDOW *window);

int32_t getIntegerFromInput(WINDOW *window, uint32_t startNumber, uint32_t maxNumber, uint32_t windowCol);

char* getStringFromInput(WINDOW *window);

#endif //INPUTTUI_H_
