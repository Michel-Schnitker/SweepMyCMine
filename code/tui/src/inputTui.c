/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include <stdlib.h>

#include "inputTui.h"
#include "types.h"
#include "string.h"
#include "globalTui.h"

#define ENTER 10
#define ESCAPE 27

WINDOW* drawInputWindow(int startCol, int startRow, char *reqString){

    WINDOW *window;
    window = malloc(sizeof(WINDOW *));
    assert(window != null);
    window = newwin(5, strlen(reqString)+2, startRow, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));
    box(window,ACS_VLINE,ACS_HLINE);

    mvwprintw(window, 1, 1, "%s", reqString);

    wrefresh(window);

    return window;
}

void deleteInputWindow(WINDOW *window){
    assert(window != null);
    (void) window;

    //todo: found Bug !?
//    delwin(window);
//    free(window);
}

int32_t getIntegerFromInput(WINDOW *window, uint32_t startNumber, uint32_t maxNumber, uint32_t windowCol){

    int key;
    uint32_t selected = startNumber;
    uint32_t textCol = (windowCol - 3 ) /2;

    mvwprintw(window, 3, textCol, "%03i", selected);
    wnoutrefresh(window);
    doupdate();

    for ever {
        key = getch();

        if (key >= '0' and key <= '9'){

            wbkgd(window, COLOR_PAIR(COLOR_MAIN_MENU));
            wnoutrefresh(window);

            selected *= 10;
            selected += key - '0';

            if (selected > maxNumber){
                selected = 0;
            }

            mvwprintw(window, 3, textCol, "%03i", selected);
            wnoutrefresh(window);
            doupdate();
        }
        else if (key == ENTER or key == ESCAPE) {

            return selected;
        }
    }
}

char* getStringFromInput(WINDOW *window){
    (void) window;

    UNREACHABLE;

    //todo: needed for HighScore ...
}
