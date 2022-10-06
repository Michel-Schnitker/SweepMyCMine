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

    return null;
}

void deleteInputWindow(WINDOW *window){
    (void) window;
}

int32_t getIntegerFromInput(WINDOW *window, uint32_t maxDigits){
    (void) window;
    (void) maxDigits;

    return 0;
}

char* getStringFromInput(WINDOW *window){
    (void) window;

    UNREACHABLE;
}
