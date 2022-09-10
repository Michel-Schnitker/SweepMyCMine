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
#include "configTui.h"
#include "highScoreTui.h"
#include "eventTui.h"
#include "tutorialTui.h"

#include "event.h"
#include "types.h"
#include "config.h"

#define ESCAPE 27


#define MENU_BAR_START_COL 2

static uint32_t terminalRow = 0, terminalCol = 0;   // row = y, col = x
static WINDOW *menubar, *statusbar, *mainWindow;


static void (*drawMainWindow[NUM_OF_MENU_ENTRIES])(uint32_t windowRow, uint32_t windowCol, WINDOW *gameWindow) ={
        [MENU_ENTRY_GAME] = drawGameWindow,
        [MENU_ENTRY_CONFIG] = drawConfigWindow,
        [MENU_ENTRY_HIGH_SCORE] = drawHighScoreWindow,
        [MENU_ENTRY_MESSAGES] = drawEventWindow,
        [MENU_ENTRY_TUTORIAL] = drawTutorialWindow,
};

static void (*drawStatusWindow[NUM_OF_MENU_ENTRIES+1])(WINDOW *window, int startCol) ={
        [MENU_ENTRY_GAME] = drawGameStatusbar,
        [MENU_ENTRY_CONFIG] = drawConfigStatusbar,
        [MENU_ENTRY_HIGH_SCORE] = drawHighScoreStatusbar,
        [MENU_ENTRY_MESSAGES] = drawEventStatusbar,
        [MENU_ENTRY_TUTORIAL] = drawTutorialStatusbar,
        [NUM_OF_MENU_ENTRIES] = drawMenuStatusbar,
};

static void (*redirectInputToMainWindow[NUM_OF_MENU_ENTRIES])(int key) ={
        [MENU_ENTRY_GAME] = redirectInputToGameWindow,
        [MENU_ENTRY_CONFIG] = redirectInputToConfigWindow,
        [MENU_ENTRY_HIGH_SCORE] = redirectInputToHighScoreWindow,
        [MENU_ENTRY_MESSAGES] = redirectInputToEventWindow,
        [MENU_ENTRY_TUTORIAL] = redirectInputToTutorialWindow,
};


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

//    disableEvent(EVENT_SUCCESS | EVENT_INFO | EVENT_TRACE | EVENT_DEBUG | EVENT_WARNING | EVENT_ERROR | EVENT_FATAL);

    initscr();
    getmaxyx(stdscr,terminalRow,terminalCol);

    curs_set(0);    // Cursor invisible
    raw();
    keypad(stdscr,TRUE);
    noecho();       // no echo of Input
}

void closeTUI(){
    delwin(mainWindow);
    delwin(menubar);
    delwin(statusbar);
    endwin();
}

void refreshMainWindow(int windowNumber){
    werase(mainWindow);
    drawMainWindow[windowNumber](terminalRow-4, terminalCol-2, mainWindow);
    wrefresh(mainWindow);
}

void refreshStatusWindow(int windowNumber){
    werase(statusbar);
    drawStatusWindow[windowNumber](statusbar, MENU_BAR_START_COL);
    wrefresh(statusbar);
}


void mainTui(){
    initTui();
    setColors();

    bkgd(COLOR_PAIR(COLOR_MAIN_BACKGROUND));

    menubar=subwin(stdscr,1,terminalCol,0,0);   //WINDOW *subwin(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x);
    statusbar=subwin(stdscr,1,terminalCol,terminalRow-1,0);
    mainWindow= subwin(stdscr,terminalRow-4,terminalCol-2,2,1);

    drawUpperMenubar(menubar, MENU_BAR_START_COL);


    initNewGame();
    refreshMainWindow(MENU_ENTRY_GAME); // as the first window draw Game Window
    refreshStatusWindow(MENU_ENTRY_GAME); // as the first window draw Game Window


    int key;
    int currentWindow = MENU_ENTRY_GAME;

    for ever{

        refresh();
        key = getch();


        if(key == ESCAPE) break;

        if(key == OPEN_MENU){
            refreshStatusWindow(NUM_OF_MENU_ENTRIES);

            WINDOW **menuItems=drawDropDownMenu(MENU_BAR_START_COL, 1);
            int32_t selectedMenuEntry = handleDropDownMenu(menuItems);
            deleteDropDownMenu(menuItems);

            //switch to selected Menu entry
            if(selectedMenuEntry >= 0 and selectedMenuEntry < NUM_OF_MENU_ENTRIES){
                currentWindow = selectedMenuEntry;
                refreshMainWindow(currentWindow);
            }

            refreshStatusWindow(currentWindow);


            touchwin(stdscr);
        }
        else{

            redirectInputToMainWindow[currentWindow](key);
            refreshMainWindow(currentWindow);
        }

    }



    closeTUI();
}