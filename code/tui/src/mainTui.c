/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include <ncurses.h>
#include <stdlib.h>

#include "mainTui.h"

#include "gameTui.h"
#include "globalTui.h"
#include "menuTui.h"

#include "event.h"
#include "types.h"
#include "config.h"

#define ESCAPE 27


#define MENU_BAR_START_COL 2

static uint32_t terminalRow = 0, terminalCol = 0;   // row = y, col = x
static WINDOW *menubar, *statusbar, *gameWindow;


void setColors(){
    start_color();
    init_pair(COLOR_CELL_CONCEALED, TUI_COLOR_BACKGROUND, TUI_COLOR_FRONT_TEXT);
    init_pair(COLOR_CELL_EMPTY, TUI_COLOR_FRONT_TEXT, TUI_COLOR_BACKGROUND);
    init_pair(COLOR_CELL_BOMB_IN_AREA, TUI_COLOR_BACKGROUND, TUI_COLOR_FRONT_GAME_NUMBER);
    init_pair(COLOR_CELL_MARKED_AS_BOMB, TUI_COLOR_BACKGROUND, TUI_COLOR_FRONT_GAME_MARKER);
    init_pair(COLOR_CELL_WRONG_MARKED_AS_BOMB, TUI_COLOR_BACKGROUND, TUI_COLOR_FRONT_GAME_WRONG_MARKER);
    init_pair(COLOR_CELL_BOMB_INSIDE, TUI_COLOR_BACKGROUND, TUI_COLOR_FRONT_GAME_BOMB);
    init_pair(COLOR_CELL_CURSOR, TUI_COLOR_BACKGROUND, TUI_COLOR_FRONT_GAME_CURSOR);

    init_pair(COLOR_MAIN_BACKGROUND,TUI_COLOR_FRONT_TEXT,TUI_COLOR_BACKGROUND);
    init_pair(COLOR_MAIN_MENU,TUI_COLOR_BACKGROUND,TUI_COLOR_FRONT_TEXT);
    init_pair(COLOR_MAIN_MENU_Akzent,TUI_COLOR_FRONT_AKZENT_TEXT,TUI_COLOR_FRONT_TEXT);
}

void initTui(){

    disableEvent(EVENT_SUCCESS | EVENT_INFO | EVENT_TRACE | EVENT_DEBUG | EVENT_WARNING | EVENT_ERROR | EVENT_FATAL);

    initscr();
    getmaxyx(stdscr,terminalRow,terminalCol);

    curs_set(0);    // Cursor invisible
    raw();
    keypad(stdscr,TRUE);
    noecho();       // no echo of Input
}

void closeTUI(){
    delwin(gameWindow);
    delwin(menubar);
    delwin(statusbar);
    endwin();
}

void mainTui(){
    initTui();
    setColors();

    bkgd(COLOR_PAIR(COLOR_MAIN_BACKGROUND));

    menubar=subwin(stdscr,1,terminalCol,0,0);   //WINDOW *subwin(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x);
    statusbar=subwin(stdscr,1,terminalCol,terminalRow-1,0);
    gameWindow= subwin(stdscr,terminalRow-4,terminalCol-2,2,1);

    drawUpperMenubar(menubar, MENU_BAR_START_COL);
//    drawMenuStatusbar(statusbar, MENU_BAR_START_COL);
    drawGameStatusbar(statusbar, MENU_BAR_START_COL);

    initNewGame();
    drawGameWindow(terminalRow-4, terminalCol-2, gameWindow);


    int key;

    for ever{

        refresh();
        key = getch();


        if(key == ESCAPE) break;

        if(key == OPEN_MENU){
            WINDOW **menuItems=drawDropDownMenu(MENU_BAR_START_COL, 1);
            int32_t selectedMenuEntry = handleDropDownMenu(menuItems);
            deleteDropDownMenu(menuItems);

            //todo: switch to selected Menu entry

            touchwin(stdscr);
        }
        else{
            //todo: key transfer to open window (game, highscore, config)
            //todo: refresh window
            redirectInputToGameWindow(key);

            drawGameWindow(terminalRow-4, terminalCol-2, gameWindow);

            wrefresh(gameWindow);
        }

    }



    closeTUI();
}