/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef MENUTUI_H_
#define MENUTUI_H_

#include "ncurses.h"

#define OPEN_MENU KEY_F(1)

enum {
    MENU_ENTRY_GAME,
    MENU_ENTRY_CONFIG,
    MENU_ENTRY_HIGH_SCORE,
    MENU_ENTRY_MESSAGES,
    MENU_ENTRY_TUTORIAL,
    NUM_OF_MENU_ENTRIES,
};


void drawUpperMenubar(WINDOW *window, int startCol);

void drawMenuStatusbar(WINDOW *window, int startCol);


WINDOW **drawDropDownMenu(int startCol, int startRow);

void deleteDropDownMenu(WINDOW **items);

int32_t handleDropDownMenu(WINDOW **items);

#endif //MENUTUI_H_
