/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "inputTui.h"
#include "types.h"

WINDOW* drawInputWindow(int startCol, int startRow, char *reqString){
    (void) startCol;
    (void) startRow;
    (void) reqString;

    //todo: draw window with request String

    return null;
}

void deleteInputWindow(WINDOW *window){
    (void) window;

    //todo: delete Window
}

int32_t getIntegerFromInput(WINDOW *window, uint32_t maxDigits){
    (void) window;
    (void) maxDigits;

    //todo: while numbers and no enter ... read numbers

    return 0;
}

char* getStringFromInput(WINDOW *window){
    (void) window;

    UNREACHABLE;

    //todo: needed for HighScore ...
}
