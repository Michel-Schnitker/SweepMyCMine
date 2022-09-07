
#include "gameTui.h"

#include "globalTui.h"

#include "ncurses.h"
#include "config.h"
#include "types.h"
#include "game.h"
#include "pos.h"

#define UP KEY_UP
#define DOWN KEY_DOWN
#define LEFT KEY_LEFT
#define RIGHT KEY_RIGHT

#define OPEN 'e'
#define MARK 'w'
#define CAPITULATION 'q'

static Pos cursor = {.x = 0, .y = 0};
static GameBoard *gameBoard = null;

void drawGameWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *gameWindow) {    // row = y, col = x

    assert(gameBoard != null);

    uint32_t row = (windowRow-SIMPLE_TUI_YSIZE_DEFAULT) /2, col = (windowCol-(SIMPLE_TUI_XSIZE_DEFAULT*3)) /2;

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

}

void initNewGame(){
    cursor.x = 0;
    cursor.y = 0;
    game_startNew(SIMPLE_TUI_XSIZE_DEFAULT,SIMPLE_TUI_YSIZE_DEFAULT,SIMPLE_TUI_BOMBS_DEFAULT);
    if(gameBoard != null) gameBoard->free(gameBoard);
    gameBoard = getGameBoard();
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
            game_mark(&cursor);
            validInput = true;
            break;

        default:
            break;
    }

    if (validInput) {

        gameBoard->free(gameBoard);
        gameBoard = getGameBoard();
    }
}

void drawGameStatusbar(WINDOW *window, int startCol){
    wmove(window,0, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(Esc)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Quit ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(w)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Mark ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(e)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Open ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(ARROWS)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Move ");
}
