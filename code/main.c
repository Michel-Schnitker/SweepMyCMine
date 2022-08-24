#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "types.h"
#include "config.h"
#include "testSuite.h"

#include "board.h"
#include "pos.h"
#include "game.h"

int main(int argc, char *argv[]) {

    runAllTests();



    printf("hello World\n");




    Board *b = createBoard(10,10,0);
    b->print(b);
    b->free(b);

    Pos *p = createPos(1,2);
    p->free(p);


}
