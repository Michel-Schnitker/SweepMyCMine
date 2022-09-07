
#include <stdlib.h>

#include "types.h"
#include "menuTui.h"
#include "globalTui.h"

#define ENTER 10
#define ESCAPE 27

#define MENU_COL_SIZE 19

static const char *Menu_Strings[] = {
        [MENU_ENTRY_GAME] = "Game",
        [MENU_ENTRY_CONFIG] = "Config",
        [MENU_ENTRY_HIGHSCORE] = "High Score",
        [MENU_ENTRY_MESSAGES] = "Messages",
};

void drawUpperMenubar(WINDOW *window, int startCol){

    wmove(window,0, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));
    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(F1)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Menu ");
}



void drawMenuStatusbar(WINDOW *window, int startCol){
    wmove(window,0, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(Esc)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Quit ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(UP & DOWN)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Change ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(ENTER)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Select ");
}


WINDOW **drawDropDownMenu(int startCol, int startRow){

    WINDOW **items;
    items=(WINDOW **)malloc(NUM_OF_MENU_ENTRYS * sizeof(WINDOW *));

    items[0]=newwin(NUM_OF_MENU_ENTRYS+1,MENU_COL_SIZE,startRow,startCol);
    wbkgd(items[0],COLOR_PAIR(COLOR_MAIN_MENU));
    box(items[0],ACS_VLINE,ACS_HLINE);

    for (int32_t i = 1; i < NUM_OF_MENU_ENTRYS; i++) {
        items[i] = subwin(items[0],1,MENU_COL_SIZE-2,i+1,startCol+1);
        wprintw(items[i],"%s",Menu_Strings[i]);
    }

    wbkgd(items[1],COLOR_PAIR(COLOR_MAIN_BACKGROUND));
    wrefresh(items[0]);
    return items;
}

void deleteDropDownMenu(WINDOW **items){

    for (int32_t i=0; i<NUM_OF_MENU_ENTRYS; i++)
        delwin(items[i]);
    free(items);
}

int32_t handleDropDownMenu(WINDOW **items){

    int key;
    int selected = 0;
    while (1) {
        key = getch();

        if (key == KEY_DOWN or key == KEY_UP) {

            wbkgd(items[selected+1], COLOR_PAIR(COLOR_MAIN_MENU));
            wnoutrefresh(items[selected+1]);

            if (key == KEY_DOWN) {

                selected=(selected+1) % (NUM_OF_MENU_ENTRYS-1);
            } else {

                selected=(selected+NUM_OF_MENU_ENTRYS - 2) % (NUM_OF_MENU_ENTRYS-1);
            }

            wbkgd(items[selected+1], COLOR_PAIR(COLOR_MAIN_BACKGROUND));
            wnoutrefresh(items[selected+1]);
            doupdate();
        }
        else if (key == ESCAPE) {

            return 0;
        }
        else if (key == ENTER) {

            assert(selected+1 > 0 and selected+1 < NUM_OF_MENU_ENTRYS);
            return selected+1;
        }
    }
}