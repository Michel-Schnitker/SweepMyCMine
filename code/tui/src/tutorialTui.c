/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "tutorialTui.h"

#include "config.h"
#include "globalTui.h"
#include "types.h"
#include "board.h"
#include "pos.h"

#define ENTER 10

static Board *tutBoard = null;

static Pos cursor = {.x = 0, .y = 0};

static Pos bombPos1 = {.x = 1, .y = 7};
static Pos bombPos2 = {.x = 9, .y = 9};
static Pos bombPos3 = {.x = 4, .y = 0};
static Pos bombPos4 = {.x = 4, .y = 3};
static Pos bombPos5 = {.x = 7, .y = 3};
static Pos bombPos6 = {.x = 6, .y = 6};

static Pos openPos1 = {.x = 0, .y = 7};

enum tutSteps{
    StartStep,
    firstMove,
    easyMove,
    MAX_TUT_STEPS,
};

static uint32_t tutStep = StartStep;

static const char *level_strings[] = {
        [StartStep] = "text1",
        [firstMove] = "text2",
        [easyMove] = "text3",
};

void createNewTutBoard(){

    if(tutBoard != null) tutBoard->free(tutBoard);
    tutBoard = null;

    List *posList = new_List();

    posList->add(posList, &bombPos1);
    posList->add(posList, &bombPos2);
    posList->add(posList, &bombPos3);
    posList->add(posList, &bombPos4);
    posList->add(posList, &bombPos5);
    posList->add(posList, &bombPos6);

    tutBoard = constructBoardByListsOfPos(10,10, posList);

    posList->delete(posList, null);
}


void drawTutorialWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window){

    uint32_t row = (windowRow-12) /2, col = (windowCol-(10*3)) /2;

    wmove(window,row,col);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));

    if(tutStep == StartStep){
        createNewTutBoard();
        cursor.y = 0, cursor.x = 0;
    }

    for (uint32_t y = 0; y < tutBoard->ySize; ++y) {
        for (uint32_t x = 0; x < tutBoard->xSize; ++x) {

            Cell cell = tutBoard->field[y][x];

            if(cell.markedAsBomb){
                wattron(window,COLOR_PAIR(COLOR_CELL_MARKED_AS_BOMB));
                if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(window, COLOR_PAIR(COLOR_CELL_CURSOR));
                wprintw(window," %s ", BOARD_SIGN_MARKASBOMB);
            }
            else{


                if(cell.concealed){
                    wattron(window,COLOR_PAIR(COLOR_CELL_CONCEALED));
                    if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(window, COLOR_PAIR(COLOR_CELL_CURSOR));
                    wprintw(window," %s ", BOARD_SIGN_CONCEALED);
                }
                else if(cell.containsBomb){
                    wattron(window,COLOR_PAIR(COLOR_CELL_BOMB_INSIDE));
                    if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(window, COLOR_PAIR(COLOR_CELL_CURSOR));
                    wprintw(window," %s ", BOARD_SIGN_BOMB);
                }
                else if(cell.bombsAround == 0){
                    wattron(window,COLOR_PAIR(COLOR_CELL_EMPTY));
                    if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(window, COLOR_PAIR(COLOR_CELL_CURSOR));
                    wprintw(window," %s ", BOARD_SIGN_EMPTY);
                }
                else{
                    wattron(window,COLOR_PAIR(COLOR_CELL_BOMB_IN_AREA));
                    if(cursor.x == (int32_t) x and cursor.y == (int32_t) y) wattron(window, COLOR_PAIR(COLOR_CELL_CURSOR));
                    wprintw(window," %i ",cell.bombsAround);
                }



            }



        }

        wmove(window,++row,col);
        wattron(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));
    }

    wmove(window,++row,col);

    wprintw(window," %s ", level_strings[tutStep]);

}


void doFirstAction(){

}

void doSecondAction(){
    tutBoard->field[0][0].concealed = false, tutBoard->field[1][0].concealed = false, tutBoard->field[2][0].concealed = false, tutBoard->field[3][0].concealed = false;
    tutBoard->field[4][0].concealed = false, tutBoard->field[5][0].concealed = false, tutBoard->field[6][0].concealed = false, tutBoard->field[8][0].concealed = false;
    tutBoard->field[9][0].concealed = false;

    tutBoard->field[0][1].concealed = false, tutBoard->field[1][1].concealed = false, tutBoard->field[2][1].concealed = false, tutBoard->field[3][1].concealed = false;
    tutBoard->field[4][1].concealed = false, tutBoard->field[5][1].concealed = false, tutBoard->field[6][1].concealed = false, tutBoard->field[8][1].concealed = false;
    tutBoard->field[9][1].concealed = false;

    tutBoard->field[0][2].concealed = false, tutBoard->field[1][2].concealed = false, tutBoard->field[2][2].concealed = false, tutBoard->field[3][2].concealed = false;
    tutBoard->field[4][2].concealed = false, tutBoard->field[5][2].concealed = false, tutBoard->field[6][2].concealed = false, tutBoard->field[7][2].concealed = false;
    tutBoard->field[8][2].concealed = false, tutBoard->field[9][2].concealed = false;

    tutBoard->field[0][3].concealed = false, tutBoard->field[1][3].concealed = false, tutBoard->field[2][3].concealed = false, tutBoard->field[3][3].concealed = false;
    tutBoard->field[4][3].concealed = false, tutBoard->field[5][3].concealed = false, tutBoard->field[6][3].concealed = false, tutBoard->field[7][3].concealed = false;
    tutBoard->field[8][3].concealed = false, tutBoard->field[9][3].concealed = false;

    tutBoard->field[4][4].concealed = false, tutBoard->field[5][4].concealed = false, tutBoard->field[6][4].concealed = false, tutBoard->field[7][4].concealed = false;
    tutBoard->field[8][4].concealed = false, tutBoard->field[9][4].concealed = false;

    tutBoard->field[0][5].concealed = false, tutBoard->field[1][5].concealed = false, tutBoard->field[2][5].concealed = false, tutBoard->field[4][5].concealed = false;
    tutBoard->field[5][5].concealed = false, tutBoard->field[6][5].concealed = false, tutBoard->field[7][5].concealed = false, tutBoard->field[8][5].concealed = false;
    tutBoard->field[9][5].concealed = false;

    tutBoard->field[0][6].concealed = false, tutBoard->field[1][6].concealed = false, tutBoard->field[2][6].concealed = false, tutBoard->field[7][6].concealed = false;
    tutBoard->field[8][6].concealed = false, tutBoard->field[9][6].concealed = false;

    tutBoard->field[0][7].concealed = false, tutBoard->field[1][7].concealed = false, tutBoard->field[2][7].concealed = false, tutBoard->field[4][7].concealed = false;
    tutBoard->field[5][7].concealed = false, tutBoard->field[6][7].concealed = false, tutBoard->field[7][7].concealed = false, tutBoard->field[8][7].concealed = false;
    tutBoard->field[9][7].concealed = false;

    tutBoard->field[0][8].concealed = false, tutBoard->field[1][8].concealed = false, tutBoard->field[2][8].concealed = false, tutBoard->field[3][8].concealed = false;
    tutBoard->field[4][8].concealed = false, tutBoard->field[5][8].concealed = false, tutBoard->field[6][8].concealed = false, tutBoard->field[7][8].concealed = false;
    tutBoard->field[8][8].concealed = false, tutBoard->field[9][8].concealed = false;

    tutBoard->field[0][9].concealed = false, tutBoard->field[1][9].concealed = false, tutBoard->field[2][9].concealed = false, tutBoard->field[3][9].concealed = false;
    tutBoard->field[4][9].concealed = false, tutBoard->field[5][9].concealed = false, tutBoard->field[6][9].concealed = false, tutBoard->field[7][9].concealed = false;
    tutBoard->field[8][9].concealed = false;

    cursor.x = 2, cursor.y = 6;
}

void doEasyAction(){
    tutBoard->field[bombPos1.y][bombPos1.x].markedAsBomb = true;
    tutBoard->field[bombPos2.y][bombPos2.x].markedAsBomb = true;
    tutBoard->field[openPos1.y][openPos1.x].concealed = false;
    cursor.x = 0, cursor.y = 7;
}


static void (*actionForStep[MAX_TUT_STEPS])() ={
        [StartStep] = doFirstAction,
        [firstMove] = doSecondAction,
        [easyMove] = doEasyAction,
};

void redirectInputToTutorialWindow(int key){

    if(key != ENTER) return;

    switch (tutStep) {
        case StartStep:
            tutStep = firstMove;
            break;
        case firstMove:
            tutStep = easyMove;
            break;
        case easyMove:
            tutStep = StartStep;
            break;
        default:
            UNREACHABLE;
    }

    actionForStep[tutStep]();

}

void drawTutorialStatusbar(WINDOW *window, int startCol){
    wmove(window,0, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(Esc)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Quit ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(ENTER)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," next Step ");
}

void openTutorialWindow(){

    tutStep = StartStep;
}

void closeTutorialWindow(){

}