/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef INPUTTUI_H_
#define INPUTTUI_H_

#include "ncurses.h"

WINDOW* drawInputWindow(int startCol, int startRow, char *reqString);

void deleteInputWindow(WINDOW *window);

int32_t getIntegerFromInput(WINDOW *window, uint32_t maxDigits);

char* getStringFromInput(WINDOW *window);

#endif //INPUTTUI_H_
