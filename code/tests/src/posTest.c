
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

void PosTest(){

    //todo: add log message

    posCloneTest();
    posCreateTest();
}
