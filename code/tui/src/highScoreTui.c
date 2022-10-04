/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "highScoreTui.h"

#include "globalTui.h"
#include "game.h"
#include "score.h"
#include "string.h"

#define SAVE TUI_SCORE_KEY_SAVE
#define RESET TUI_SCORE_KEY_RESET

#define LENGTH_OF_SCORE_STRING 10

void printScoreString( WINDOW *window, ScoreEntry *score, uint32_t row, uint32_t windowCol){

    uint32_t textCol = (windowCol - LENGTH_OF_SCORE_STRING) /2;
    wmove(window,row,textCol);

    if(score->name == null){
        wprintw(window,"%02i ... 999", score->rang );
    }
    else{
        wprintw(window,"%02i %s %-3li", score->rang, score->name, score->time );
    }
}

void drawHighScoreWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window){
    (void) windowCol;

    uint32_t row = (windowRow- ((MAX_GAME_LEVELS-1) * (SCORE_NUMBER_SCORES_TO_SAVED +2) )) /2, col = 0;

    wbkgd(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));
    wattron(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));

    for (int level = GAME_LEVEL_BEGINNER; level < MAX_GAME_LEVELS; ++level) {

        uint32_t textCol = (windowCol - strlen(GameLevel_strings[level])) /2;
        wmove(window,row,textCol);

        wprintw(window,"%s", GameLevel_strings[level]);
        wmove(window,++row,col);

        for (int rang = 1; rang < SCORE_NUMBER_SCORES_TO_SAVED+1; ++rang) {
            ScoreEntry *score = getScoreEntry(level, rang);


            printScoreString(window, score, row, windowCol);
            row++;

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
