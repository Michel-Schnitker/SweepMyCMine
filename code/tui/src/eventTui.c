/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "eventTui.h"

#include "globalTui.h"

static int lastInput;

void drawEventWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window){
    wmove(window,0,0);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));


    //todo: implement


    wprintw(window," MainWindow of Event, Input: %i", lastInput);
}

void redirectInputToEventWindow(int key){
    lastInput = key;

    //todo: implement

}

void drawEventStatusbar(WINDOW *window, int startCol){
    wmove(window,0, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));


    //todo: implement


    waddstr(window," Statusbar of Event ");
}
