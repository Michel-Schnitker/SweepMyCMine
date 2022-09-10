/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "config.h"
#include "testSuite.h"

#include "event.h"

#include "mainTui.h"

int main(int argc, char *argv[]) {

    assert(argc == 1);

    startEventLogging(DIREKT_PRINT);

    runAllTests();

    startEventLogging(USE_LOG_BUFFER | PRINT_TO_FILE);

    mainTui();

    stopEventLogging();


//    print_success("print_success");
//    print_info("print_info");
//    print_trace("print_trace");
//    print_debug("print_debug");
//    print_warning("print_warn");
//    print_error("print_error");
//    print_fatal("print_fatal");


//    Board *b = constructFullyRandomBoard(10,10,30);
//    b->print(b);
//    b->free(b);


//    game_startNew(10,10,40);
//    Board *board = game_debugReturnBoard();
//    board->print(board);
//    Pos pos1 ={ .x = 2, .y = 3 };
//    game_open(&pos1);
//    board->print(board);

//    Pos *p = new_Pos(1,2);
//    p->free(p);

    return SUCCESS;
}
