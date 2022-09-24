/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "gameTui.h"

#include "globalTui.h"

#include "ncurses.h"
#include "config.h"
#include "types.h"
#include "game.h"
#include "pos.h"
#include "mainSolver.h"
#include "feature.h"

#define UP TUI_GAME_KEY_UP
#define DOWN TUI_GAME_KEY_DOWN
#define LEFT TUI_GAME_KEY_LEFT
#define RIGHT TUI_GAME_KEY_RIGHT

#define OPEN TUI_GAME_KEY_OPEN
#define MARK TUI_GAME_KEY_MARK
#define CAPITULATION TUI_GAME_KEY_CAPITULATION
#define HELP TUI_GAME_KEY_HELPER
#define SOLVE TUI_GAME_KEY_SOLVER

static Pos cursor = {.x = 0, .y = 0};
static GameBoard *gameBoard = null;
static Features *features = null;

void drawGameWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *gameWindow) {    // row = y, col = x

    assert(gameBoard != null);

    uint32_t row = (windowRow- gameBoard->ySize -2) /2, col = (windowCol-( gameBoard->xSize *3)) /2;

    wmove(gameWindow,row,col);
    wbkgd(gameWindow,COLOR_PAIR(COLOR_MAIN_BACKGROUND));
    wattron(gameWindow,COLOR_PAIR(COLOR_MAIN_BACKGROUND));

    for (uint32_t y = 0; y < gameBoard->ySize; ++y) {
        for (uint32_t x = 0; x < gameBoard->xSize; ++x) {

            enum CellState state = gameBoard->field[y][x];

            if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(gameWindow, COLOR_PAIR(COLOR_CELL_CURSOR));

            switch (state) {

                case CELL_EMPTY:
                    wattron(gameWindow,COLOR_PAIR(COLOR_CELL_EMPTY));
                    if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(gameWindow, COLOR_PAIR(COLOR_CELL_CURSOR));
                    wprintw(gameWindow," %s ", BOARD_SIGN_EMPTY);
                    break;

                case CELL_BOMB_IN_AREA_ONE ... CELL_BOMB_IN_AREA_EIGHT:
                    wattron(gameWindow,COLOR_PAIR(COLOR_CELL_BOMB_IN_AREA));
                    if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(gameWindow, COLOR_PAIR(COLOR_CELL_CURSOR));
                    wprintw(gameWindow," %c ",state+'0');
                    break;

                case CELL_CONCEALED:
                    wattron(gameWindow,COLOR_PAIR(COLOR_CELL_CONCEALED));
                    if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(gameWindow, COLOR_PAIR(COLOR_CELL_CURSOR));
                    wprintw(gameWindow," %s ", BOARD_SIGN_CONCEALED);
                    break;

                case CELL_BOMB_INSIDE:
                    wattron(gameWindow,COLOR_PAIR(COLOR_CELL_BOMB_INSIDE));
                    if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(gameWindow, COLOR_PAIR(COLOR_CELL_CURSOR));
                    wprintw(gameWindow," %s ", BOARD_SIGN_BOMB);
                    break;

                case CELL_MARKED_AS_BOMB:
                    wattron(gameWindow,COLOR_PAIR(COLOR_CELL_MARKED_AS_BOMB));
                    if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(gameWindow, COLOR_PAIR(COLOR_CELL_CURSOR));
                    wprintw(gameWindow," %s ", BOARD_SIGN_MARKASBOMB);
                    break;

                case CELL_WRONG_MARK_AS_BOMB:
                    wattron(gameWindow,COLOR_PAIR(COLOR_CELL_WRONG_MARKED_AS_BOMB));
                    if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(gameWindow, COLOR_PAIR(COLOR_CELL_CURSOR));
                    wprintw(gameWindow," %s ", BOARD_SIGN_WRONGMARKER);
                    break;

                default:
                    UNREACHABLE;
                    break;

            }
        }

        wmove(gameWindow,++row,col);
    }
    wattron(gameWindow,COLOR_PAIR(COLOR_MAIN_BACKGROUND));
    wmove(gameWindow,++row,col);
    wprintw(gameWindow, "Missing Bombs :%03i ", gameBoard->cellsToBeFound);
    col += (( gameBoard->xSize *3)-12);
    wmove(gameWindow,row,col);
    wprintw(gameWindow, "Seconds :%03li ", gameBoard->runtime);

    if(gameBoard->gameFinish){

        col = (windowCol-10) /2;
        wmove(gameWindow,row,col);

        if(gameBoard->gameWon){
            wattron(gameWindow,COLOR_PAIR(COLOR_CELL_CURSOR));
            wprintw(gameWindow, " YOU  WIN ");
        }
        else{
            wattron(gameWindow,COLOR_PAIR(COLOR_CELL_BOMB_INSIDE));
            wprintw(gameWindow, " YOU LOSE ");
        }
    }

    wattron(gameWindow,COLOR_PAIR(COLOR_MAIN_BACKGROUND));
}

void initNewGame(){
    cursor.x = 0;
    cursor.y = 0;
    game_startLevel(GAME_LEVEL_EXPERT);
    if(gameBoard != null) gameBoard->free(gameBoard);
    gameBoard = getGameBoard();
}

void refreshGameBoard(){
    if(gameBoard != null) gameBoard->free(gameBoard);
    gameBoard = getGameBoard();
}

void refreshFeatures(){
    if(features != null) free(features);
    features = getGameFeatures();
}

void redirectInputToGameWindow(int key) {

    Pos nextPos = {.x = cursor.x, .y = cursor.y};
    bool validInput = false;

    if (gameBoard == null or gameBoard->gameFinish) {
        initNewGame();
    }

    switch (key) {

        case RIGHT:
            nextPos.x++;
            if (gameBoard->validPos(&nextPos)) {
                cursor.x++;
                validInput = true;
            }
            break;

        case LEFT:
            nextPos.x--;
            if (gameBoard->validPos(&nextPos)) {
                cursor.x--;
                validInput = true;
            }
            break;

        case UP:
            nextPos.y--;
            if (gameBoard->validPos(&nextPos)) {
                cursor.y--;
                validInput = true;
            }
            break;

        case DOWN:
            nextPos.y++;
            if (gameBoard->validPos(&nextPos)) {
                cursor.y++;
                validInput = true;
            }
            break;

        case CAPITULATION:
            game_capitulation();
            validInput = true;
            break;

        case OPEN:
            game_open(&cursor);
            validInput = true;
            break;

        case MARK:
            if(features->nonFlagging) break;
            game_mark(&cursor);
            validInput = true;
            break;

        case HELP:
            if(not features->solverAllowed) break;
            solver_singleGameStep();
            validInput = true;
            break;

        case SOLVE:
            if(not features->solverAllowed) break;
            solver_finishGame();
            validInput = true;
            break;

        default:
            break;
    }

    if (validInput) {

        refreshGameBoard();
    }
}

void drawGameStatusbar(WINDOW *window, int startCol){
    wmove(window,0, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(Esc)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Quit ");

    if (not features->nonFlagging){

        wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
        wprintw(window,"(%c)", MARK);
        wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
        waddstr(window," Mark ");
    }

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    wprintw(window,"(%c)", OPEN);
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Open ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(ARROWS)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Move ");

    if (features->solverAllowed){

        wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
        wprintw(window,"(%c)", HELP);
        wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
        waddstr(window," Help ");

        wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
        wprintw(window,"(%c)", SOLVE);
        wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
        waddstr(window," Solve ");
    }

}

void openGameWindow(){

    refreshGameBoard();
    refreshFeatures();

    if(gameBoard == null){
        initNewGame();
    }
}

void closeGameWindow(){

}
