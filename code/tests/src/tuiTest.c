
#include "tuiTest.h"
#include "event.h"
#include <ncurses.h>

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