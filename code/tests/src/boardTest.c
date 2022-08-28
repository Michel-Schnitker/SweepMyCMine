#include "boardTest.h"
#include "board.h"
#include "event.h"

void FullyRandomTest(){

    print_info("    Running fully random board construct test ...");

    //todo: test1

    Board *testBoard = constructFullyRandomBoard(10,10,10);

    //todo: test1

    testBoard->free(testBoard);

    print_warning("         Test not implement ...");
}

void BoardWithBombproofPosTest(){

    print_info("    Running construct board test with bombproof pos ...");

    //todo: test1

    Pos *bombproofPos = new_Pos(2,3);
    Board *testBoard = constructRandBoardWithBombproofPos(10,10,10, bombproofPos);
    bombproofPos->free(bombproofPos);

    //todo: test1

    testBoard->free(testBoard);


    print_warning("         Test not implement ...");
}

void BoardByBombListTest(){

    print_info("    Running construct board test with list of bombs ...");

    //todo: test1

    List *bombList = new_List();
    bombList->add(bombList, new_Pos(2,3));
    bombList->add(bombList, new_Pos(1,2));

    Board *testBoard = constructBoardByListsOfPos(10,10,bombList);
    Pos *pos = bombList->getFirst(bombList);
    bombList->delete(bombList, (void*)(void *) pos->free);

    //todo: test1

    testBoard->free(testBoard);

    print_warning("         Test not implement ...");
}

void boardTest(){

    print_info("Running Tests for board.c");

    FullyRandomTest();
    BoardWithBombproofPosTest();
    BoardByBombListTest();
}
