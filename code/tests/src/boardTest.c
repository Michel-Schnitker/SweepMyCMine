#include "boardTest.h"
#include "board.h"
#include "event.h"

typedef struct TestCounter {
    uint32_t bombs;
    uint32_t concealed;
    uint32_t marked;
    uint32_t bombsInArea;
} TestCounter;

void _countingField(Board *testBoard, TestCounter * count){
    count->concealed = count->marked = count->bombsInArea = count->bombs = 0;

    for (uint32_t y = 0; y < testBoard->ySize; ++y) {
        for (uint32_t x = 0; x < testBoard->xSize; ++x) {

            if(testBoard->field[y][x].containsBomb){
                count->bombs++;
            }
            else{
                count->bombsInArea += testBoard->field[y][x].bombsAround;
            }

            if(testBoard->field[y][x].concealed){
                count->concealed++;
            }

            if(testBoard->field[y][x].markedAsBomb){
                count->marked++;
            }
        }
    }

}

//todo: implement test for number bombsAround


void FullyRandomTest(){

    print_info("    Running fully random board construct test ...");

    Board *testBoard = constructFullyRandomBoard(2,2,2);

    TestCounter counter;
    _countingField(testBoard, &counter);

    nonNull(testBoard->free);
    nonNull(testBoard->print);

    assert(testBoard->xSize == 2 and testBoard->ySize == 2 and testBoard->bombs == 2);
    assert(testBoard->openCells == 0 and testBoard->bombMarkers == 0);
    assert(not testBoard->gameStarted and not testBoard->gameFinish and not testBoard->gameWon);

    assert(counter.bombsInArea == 4);
    assert(counter.bombs == 2);
    assert(counter.concealed == 4);
    assert(counter.marked == 0);

    //todo: extend test

    testBoard->free(testBoard);

    print_success("         Passed ...");
}

void BoardWithBombproofPosTest(){

    print_info("    Running construct board test with bombproof pos ...");

    Pos *bombproofPos = new_Pos(2,3);
    Board *testBoard = constructRandBoardWithBombproofPos(10,10,10, bombproofPos);
    bombproofPos->free(bombproofPos);

    //todo: extend test

    TestCounter counter;
    _countingField(testBoard, &counter);

    assert(counter.bombsInArea > 8);
    assert(counter.bombs == 10);
    assert(counter.concealed == 100);
    assert(counter.marked == 0);

    assert(testBoard->bombs == 10);
    assert(not testBoard->field[3][2].containsBomb);

    testBoard->free(testBoard);


    print_success("         Passed ...");
}

void BoardByBombListTest(){

    print_info("    Running construct board test with list of bombs ...");

    List *bombList = new_List();
    bombList->add(bombList, new_Pos(2,3));
    bombList->add(bombList, new_Pos(1,2));

    Board *testBoard = constructBoardByListsOfPos(10,10,bombList);
    Pos *pos = bombList->getFirst(bombList);
    bombList->delete(bombList, (void*)(void *) pos->free);

    //todo: extend test

    TestCounter counter;
    _countingField(testBoard, &counter);

    assert(counter.bombsInArea > 4);
    assert(counter.bombs == 2);
    assert(counter.concealed == 100);
    assert(counter.marked == 0);

    assert(testBoard->bombs == 2);
    assert(testBoard->field[3][2].containsBomb);
    assert(testBoard->field[2][1].containsBomb);

    testBoard->free(testBoard);

    print_success("         Passed ...");
}

void boardTest(){

    print_info("Running Tests for board.c");

    FullyRandomTest();
    BoardWithBombproofPosTest();
    BoardByBombListTest();
}
