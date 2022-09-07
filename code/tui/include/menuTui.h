
#ifndef MENUTUI_H_
#define MENUTUI_H_

#include "ncurses.h"

#define OPEN_MENU KEY_F(1)

enum {
    // 0 is reserviert for the frame
    MENU_ENTRY_GAME = 1,
    MENU_ENTRY_CONFIG = 2,
    MENU_ENTRY_HIGHSCORE = 3,
    MENU_ENTRY_MESSAGES = 4,
    NUM_OF_MENU_ENTRYS,
};


void drawUpperMenubar(WINDOW *window, int startCol);

void drawMenuStatusbar(WINDOW *window, int startCol);


WINDOW **drawDropDownMenu(int startCol, int startRow);

void deleteDropDownMenu(WINDOW **items);

int32_t handleDropDownMenu(WINDOW **items);

#endif //MENUTUI_H_
