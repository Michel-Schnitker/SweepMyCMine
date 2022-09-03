
#include <ncurses.h>

#include "simpleTui.h"

#include "event.h"
#include "types.h"
#include "config.h"
#include "game.h"
#include "pos.h"

static Pos cursor = {.x = 0, .y = 0};

enum ColorSet{
    COLOR_CONCEALED = 1,
    COLOR_EMPTY = 2,
    COLOR_BOMB_IN_AREA = 3,
    COLOR_MARKED_AS_BOMB = 4,
    COLOR_BOMB = 5,
};

void setColors(){
    start_color();
    init_pair(COLOR_CONCEALED, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_EMPTY, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_BOMB_IN_AREA, COLOR_BLACK, COLOR_YELLOW);
    init_pair(COLOR_MARKED_AS_BOMB, COLOR_BLACK, COLOR_BLUE);
    init_pair(COLOR_BOMB, COLOR_BLACK, COLOR_RED);
}

void horizontalBorder(uint32_t size){
    attron(COLOR_PAIR(COLOR_CONCEALED));
    printw(" +");
    for (uint32_t x = 0; x < size*3; ++x) {
        printw("-");
    }
    printw("+ ");
}

void printField(GameBoard *gameBoard){

    uint32_t row = 2, col = 3;

    move(row,col);

    horizontalBorder(gameBoard->xSize);
    move(++row,col);

    for (uint32_t y = 0; y < gameBoard->ySize; ++y) {

        attron(COLOR_PAIR(COLOR_CONCEALED));
        printw(" |");
        for (uint32_t x = 0; x < gameBoard->xSize; ++x) {

            attrset(A_NORMAL);
            enum CellState state = gameBoard->field[y][x];

            if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) attrset(A_REVERSE);

            switch (state) {

                case CELL_EMPTY:
                    attron(COLOR_PAIR(COLOR_EMPTY));
                    printw("   ");
                    break;

                case CELL_BOMB_IN_AREA_ONE ... CELL_BOMB_IN_AREA_EIGHT:
                    attron(COLOR_PAIR(COLOR_BOMB_IN_AREA));
                    printw(" %c ",state + '0');
                    break;

                case CELL_CONCEALED:
                    attron(COLOR_PAIR(COLOR_CONCEALED));
                    printw(" %s ", BOARD_SIGN_CONCEALED);
                    break;

                case CELL_BOMB_INSIDE:
                    attron(COLOR_PAIR(COLOR_BOMB));
                    printw(" %s ", BOARD_SIGN_BOMB);
                    break;

                case CELL_MARKED_AS_BOMB:
                    attron(COLOR_PAIR(COLOR_MARKED_AS_BOMB));
                    printw(" %s ", BOARD_SIGN_MARKASBOMB);
                    break;

                default:
                    UNREACHABLE;
                    break;

            }

            attrset(A_NORMAL);

        }
        attron(COLOR_PAIR(COLOR_CONCEALED));
        printw("| ");
        move(++row,col);

    }

    horizontalBorder(gameBoard->xSize);
    move(++row,col);
    move(++row,col);
    printw("(q) -> quit | (e) -> open | (w) -> mark | Arrows to navigate | Missing Bombs: %i", gameBoard->cellsToBeFound);
}


void simpleNcurseTui(){

    disableEvent(EVENT_SUCCESS | EVENT_INFO | EVENT_TRACE | EVENT_DEBUG | EVENT_WARNING | EVENT_ERROR | EVENT_FATAL);

    initscr();
    raw();
    keypad(stdscr,TRUE);
    noecho();

    setColors();

    game_startNew(SIMPLE_TUI_XSIZE_DEFAULT,SIMPLE_TUI_YSIZE_DEFAULT,SIMPLE_TUI_BOMBS_DEFAULT);
    GameBoard *gameBoard = getGameBoard();

    do{
        printField(gameBoard);

        bool validInput = false;
        while (not validInput){

            Pos nextPos = {.x = cursor.x, .y = cursor.y};
            switch (getch()) {

                case KEY_RIGHT:
                    nextPos.x++;
                    if(gameBoard->validPos(&nextPos)){
                        cursor.x++;
                        validInput = true;
                    }
                    break;

                case KEY_LEFT:
                    nextPos.x--;
                    if(gameBoard->validPos(&nextPos)){
                        cursor.x--;
                        validInput = true;
                    }
                    break;

                case KEY_UP:
                    nextPos.y--;
                    if(gameBoard->validPos(&nextPos)){
                        cursor.y--;
                        validInput = true;
                    }
                    break;

                case KEY_DOWN:
                    nextPos.y++;
                    if(gameBoard->validPos(&nextPos)){
                        cursor.y++;
                        validInput = true;
                    }
                    break;

                case 'q':
                    game_capitulation();
                    validInput = true;
                    break;

                case 'e':
                    game_open(&cursor);
                    validInput = true;
                    break;

                case 'w':
                    game_mark(&cursor);
                    validInput = true;
                    break;

                default:
                    break;
            }
        }

        gameBoard->free(gameBoard);
        gameBoard = getGameBoard();

    } while (!gameBoard->gameFinish);

    printField(gameBoard);

    if(gameBoard->gameWon){
        printw("\n\nGame won");
    }
    else{
        printw("\n\nGame lose");
    }

    getch();
    endwin();

}
