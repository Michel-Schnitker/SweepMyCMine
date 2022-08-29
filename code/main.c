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


int main(int argc, char *argv[]) {

    runAllTests();



    printf("\nhello World\n");






//    print_success("print_success");
//    print_info("print_info");
//    print_trace("print_trace");
//    print_debug("print_debug");
//    print_warning("print_warn");
//    print_error("print_error");
//    print_fatal("print_fatal");


    Board *b = constructFullyRandomBoard(10,10,30);
    b->print(b);
    b->free(b);

//    Pos *p = new_Pos(1,2);
//    p->free(p);


}
