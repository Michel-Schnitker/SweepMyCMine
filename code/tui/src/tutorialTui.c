/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "tutorialTui.h"

#include "globalTui.h"
#include "types.h"
#include "game.h"
#include "pos.h"

static int lastInput;

void drawTutorialWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window){
    wmove(window,0,0);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));


    //todo: implement


    wprintw(window," MainWindow of Tutorial, Input: %i", lastInput);
}

void redirectInputToTutorialWindow(int key){
    lastInput = key;

    //todo: implement

}

void drawTutorialStatusbar(WINDOW *window, int startCol){
    wmove(window,0, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));


    //todo: implement


    waddstr(window," Statusbar of Tutorial ");
}
