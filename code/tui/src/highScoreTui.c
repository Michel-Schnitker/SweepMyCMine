/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "highScoreTui.h"

#include "globalTui.h"
#include "game.h"
#include "score.h"

#define SAVE TUI_SCORE_KEY_SAVE
#define RESET TUI_SCORE_KEY_RESET

void drawHighScoreWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window){
    (void) windowCol;

    uint32_t row = (windowRow- (MAX_GAME_LEVELS * (SCORE_NUMBER_SCORES_TO_SAVED +2) )) /2, col = 0;

    wmove(window,row,col);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));

    for (int i = GAME_LEVEL_BEGINNER; i < MAX_GAME_LEVELS; ++i) {

        wprintw(window," %s ", GameLevel_strings[i]);
        wmove(window,++row,col);

        for (int j = 1; j < SCORE_NUMBER_SCORES_TO_SAVED+1; ++j) {
            ScoreEntry *score = getScoreEntry(i, j);

            if(score->name == null){
                wprintw(window,"%i ... 999", score->rang );
            }
            else{
                wprintw(window,"%i %s %li", score->rang, score->name, score->time );
            }

            wmove(window,++row,col);

            score->free(score);
        }
        wmove(window,++row,col);
    }
}

void redirectInputToHighScoreWindow(int key){

    switch (key) {

        case SAVE:
            saveScores();
            break;

        case RESET:
            resetScores();
            break;

        default:
            break;
    }
}

void drawHighScoreStatusbar(WINDOW *window, int startCol){
    wmove(window,0, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(Esc)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Quit ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    wprintw(window,"(%c)", SAVE);
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Save ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    wprintw(window,"(%c)", RESET);
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Reset ");
}

void openHighScoreWindow(){

}

void closeHighScoreWindow(){

}
