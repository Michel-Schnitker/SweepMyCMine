/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "string.h"

#include "eventTui.h"

#include "types.h"
#include "globalTui.h"
#include "event.h"


void drawEventWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window){

    uint32_t row = (windowRow - getEventBufferSize()) / 2, col = 4;

    wmove(window,row,col);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));

    EventElement *event = getEventMessageFromLog();

    if(event == null){
        uint32_t textCol = (windowCol-22) /2;
        wmove(window,row,textCol);
        wprintw(window, "no messages available.");
    }

    while (event != null and row <= windowRow){

        switch (event->level) {
            case EVENT_SUCCESS:
                wattron(window, COLOR_PAIR(COLOR_CELL_CURSOR));
                break;
            case EVENT_TRACE:
            case EVENT_DEBUG:
                wattron(window,COLOR_PAIR(COLOR_CELL_MARKED_AS_BOMB));
                break;
            case EVENT_WARNING:
                wattron(window,COLOR_PAIR(COLOR_CELL_BOMB_IN_AREA));
                break;
            case EVENT_ERROR:
            case EVENT_FATAL:
                wattron(window,COLOR_PAIR(COLOR_CELL_WRONG_MARKED_AS_BOMB));
                break;
            case EVENT_INFO:
            default:
                wattron(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));
                break;
        }

        uint32_t textCol = (windowCol-(strlen(event->metaString) + strlen(event->pathString) + strlen(event->messageString) + 2)) /2;
        wmove(window,row,textCol);
        wprintw(window, "%s %s %s", event->metaString, event->pathString, event->messageString);
        wmove(window,++row,col);
        event = getEventMessageFromLog();
    }

    wattron(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));
}

void redirectInputToEventWindow(int key){
    (void) key;

}

void drawEventStatusbar(WINDOW *window, int startCol){
    wmove(window,0, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(Esc)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Quit ");
}

void openEventWindow(){

}

void closeEventWindow(){

}
