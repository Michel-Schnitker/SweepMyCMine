/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "highScoreTui.h"

#include "globalTui.h"

static int lastInput;

void drawHighScoreWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window){
    (void) windowCol;
    (void) windowRow;

    wmove(window,0,0);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));


    //todo: implement


    wprintw(window," MainWindow of HighScore, Input: %i", lastInput);
}

void redirectInputToHighScoreWindow(int key){
    lastInput = key;

    //todo: implement

}

void drawHighScoreStatusbar(WINDOW *window, int startCol){
    wmove(window,0, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));


    //todo: implement


    waddstr(window," Statusbar of HighScore ");
}

void openHighScoreWindow(){

}

void closeHighScoreWindow(){

}
