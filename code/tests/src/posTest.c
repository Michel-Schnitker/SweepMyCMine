
#include "posTest.h"
#include "pos.h"

void posCreateTest(){

    //todo: add log message

    Pos * p = createPos(2,3);
    assert(p->x == 2);
    assert(p->y == 3);
    p->free(p);
}

void posCloneTest(){

    //todo: add log message

    Pos *p = createPos(2,3);
    Pos *w = p->clone(p);
    assert(p != w);
    assert(w->x == 2);
    assert(w->y == 3);
    p->free(p);
    w->free(w);
}

void posCompareTest(){

    //todo: add log message

    Pos * p = createPos(2,3);
    Pos * b = createPos(2,3);
    assert(p != b);
    assert(p->compare(p, b));

    Pos *c = createPos(3,2);
    assert(not p->compare(p, c));

    p->free(p);
    b->free(b);
    c->free(c);
}

void posTest(){

    //todo: add log message

    posCloneTest();
    posCreateTest();
}
