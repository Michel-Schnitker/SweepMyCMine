/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "posTest.h"
#include "pos.h"
#include "event.h"

void posCreateTest(){

    print_info("    Running Tests for create Pos ...");

    Pos * p = new_Pos(2,3);

    nonNull(p->free);
    nonNull(p->clone);
    nonNull(p->print);
    nonNull(p->compare);

    ifPrint_fatal(p->x != 2, "         x value is wrong after create new Pos.");
    ifPrint_fatal(p->y != 3, "         y value is wrong after create new Pos.");

    p->free(p);

    print_success("         Passed");
}

void posCloneTest(){

    print_info("    Running Tests for clone Pos ...");

    Pos *p = new_Pos(2,3);
    Pos *w = p->clone(p);

    ifPrint_fatal(p == w, "         Pointer of p and w is the same.");
    ifPrint_fatal(w->x != 2, "         x value is wrong after clone a Pos.");
    ifPrint_fatal(w->y != 3, "         y value is wrong after clone a Pos.");

    p->free(p);
    w->free(w);

    print_success("         Passed");
}

void posCompareTest(){

    print_info("    Running Tests for compare Pos ...");

    Pos * p = new_Pos(2,3);
    Pos * b = new_Pos(2,3);
    ifPrint_fatal(p == b, "         Pointer of p and b is the same.");
    ifPrint_fatal( not p->compare(p, b), "         The compare of p and b failed.");

    Pos *c = new_Pos(3,2);
    ifPrint_fatal(p == c, "         Pointer of p and c is the same.");
    ifPrint_fatal( p->compare(p, c), "         The compare of p and c is false true.");

    p->free(p);
    b->free(b);
    c->free(c);

    print_success("         Passed");
}

void posInRangeTest(){

    print_info("    Running Tests for random Pos in Range ...");

    Pos *randomPos = getRandomPosInRange(3,4,7,8);

    ifPrint_fatal(randomPos->x != 3 and randomPos->x != 4, "         x Value of random Pos not in range.");
    ifPrint_fatal(randomPos->y != 7 and randomPos->y != 8, "         y Value of random Pos not in range.");

    randomPos->free(randomPos);

    print_success("         Passed");
}

void posTest(){

    print_info("Running Tests for pos.c");

    posCreateTest();
    posCloneTest();
    posCompareTest();
    posInRangeTest();
}
