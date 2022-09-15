/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "tuiTest.h"
#include "event.h"
#include <ncurses.h>

//todo: exchange from assert to ifPrint_Fatal

void tuiColorTest(){

    print_info("    Running Tests for using colors ...");

    initscr();

    if(has_colors() == FALSE){
        endwin();
        print_error("Your terminal does not support color");
        assert(false);
    }
    endwin();

    print_success("         Passed");
}

void tuiTest(){

    print_info("Running Tests for tui");

    tuiColorTest();
}