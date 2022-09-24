/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "tuiTest.h"
#include "event.h"
#include <ncurses.h>

void tuiColorTest(){

    print_info("    Running Tests for using colors ...");

    initscr();

    if(has_colors() == FALSE){
        endwin();
        ifPrint_fatal(true, "         Your terminal does not support color");
    }
    endwin();

    print_success("         Passed");
}

void tuiTest(){

    print_info("Running Tests for tui");

    tuiColorTest();
}
