#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "types.h"
#include "config.h"
#include "testSuite.h"

#include "event.h" //todo: delete
#include "board.h" //todo: delete
#include "pos.h" //todo: delete
#include "game.h"

#include "simpleTui.h"

int main(int argc, char *argv[]) {

    assert(argc == 1);
    runAllTests();



    printf("\nhello World\n");


    simpleNcurseTui();



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
