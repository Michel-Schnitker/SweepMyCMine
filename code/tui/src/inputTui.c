/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include <stdlib.h>

#include "inputTui.h"
#include "types.h"
#include "string.h"
#include "globalTui.h"

#define ENTER 10
#define ESCAPE 27
#define RETURN 263

WINDOW* drawInputWindow(int startCol, int startRow, char *reqString){

    WINDOW *window = newwin(5, strlen(reqString)+2, startRow, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));
    box(window,ACS_VLINE,ACS_HLINE);

    mvwprintw(window, 1, 1, "%s", reqString);

    wrefresh(window);

    return window;
}

void deleteInputWindow(WINDOW *window){
    assert(window != null);

    delwin(window);
}

int32_t getIntegerFromInput(WINDOW *window, uint32_t startNumber, uint32_t maxNumber, uint32_t windowCol){

    int key;
    uint32_t selected = startNumber;
    uint32_t textCol = (windowCol - 3 ) /2;

    wbkgd(window, COLOR_PAIR(COLOR_MAIN_MENU));
    wnoutrefresh(window);

    mvwprintw(window, 3, textCol, "%03i", selected);
    wrefresh(window);

    for ever {
        key = getch();

        if (key >= '0' and key <= '9'){

            selected *= 10;
            selected += key - '0';

            if (selected > maxNumber){
                selected = 0;
            }
        }
        else if (key == RETURN) {

            selected /= 10;
        }
        else if (key == ENTER or key == ESCAPE) {

            return selected;
        }

        mvwprintw(window, 3, textCol, "%03i", selected);
        wrefresh(window);
    }
}

char* getStringFromInput(WINDOW *window, uint32_t maxDigits, uint32_t windowCol){

    int key;
    char *string = malloc((maxDigits+1) * sizeof(char));
    uint32_t count = 0;
    uint32_t textCol = (windowCol +2 - maxDigits ) /2;

    for (int i = 0; i < maxDigits; ++i) {
        string[i] = '_';
    }
    string[maxDigits] = '\0';

    mvwprintw(window, 3, textCol, "%s", string);
    wrefresh(window);

    for ever {
        key = getch();

        if ((isAlphabetKey(key) or isNumberKey(key))){

            if(count < maxDigits) {
                string[count] = (char) key;
                count++;
            }
        }
        else if (key == RETURN) {

            if(count > 0) {
                count--;
                string[count] = '_';
            }
        }
        else if (key == ENTER) {

            return string;
        }
        else if (key == ESCAPE) {

            free(string);
            return null;
        }

        mvwprintw(window, 3, textCol, "%s", string);
        wrefresh(window);
    }
}
