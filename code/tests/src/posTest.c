
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

    assert(p->x == 2);
    assert(p->y == 3);

    p->free(p);

    print_success("         Passed");
}

void posCloneTest(){

    print_info("    Running Tests for clone Pos ...");

    Pos *p = new_Pos(2,3);
    Pos *w = p->clone(p);

    assert(p != w);
    assert(w->x == 2);
    assert(w->y == 3);

    p->free(p);
    w->free(w);

    print_success("         Passed");
}

void posCompareTest(){

    print_info("    Running Tests for compare Pos ...");

    Pos * p = new_Pos(2,3);
    Pos * b = new_Pos(2,3);
    assert(p != b);
    assert(p->compare(p, b));

    Pos *c = new_Pos(3,2);
    assert(not p->compare(p, c));

    p->free(p);
    b->free(b);
    c->free(c);

    print_success("         Passed");
}

void posTest(){

    print_info("Running Tests for pos.c");

    posCreateTest();
    posCloneTest();
    posCompareTest();
}
