
#include "config.h"
#include "gameTest.h"
#include "game.h"
#include "pos.h"
#include "event.h"

void gameWonTest(){

    print_info("    Running Tests for win a game ...");

    //todo: deactivate print_warnings

#if START_WITH_FIRST_SAFE_POS
    Pos pos1 = {.x = 0, .y = 0};    // FirstPos
    Board *board = constructRandBoardWithBombproofPos(5,5,2,&pos1);

#else
    Board *board = constructFullyRandomBoard(5,5,2);

#endif

    game_startThis(board);

    assert(board->gameFinish == false);
    assert(board->gameStarted == false);
    assert(board->openCells == 0);
    assert(board->xSize == 5 and board->ySize == 5 and board->bombs == 2);

    for (uint32_t y = 0; y < board->ySize; ++y) {
        for (uint32_t x = 0; x < board->xSize; ++x) {

            if(board->gameFinish){ break;}

            if(not board->field[y][x].containsBomb and board->field[y][x].concealed){
                Pos pos = {.x = x, .y = y};
                game_open(&pos);
            }
        }
    }

    assert(board->gameStarted == true);
    assert(board->gameFinish == true);
    assert(board->gameWon == true);
    assert(board->bombs == 25 - board->openCells);

    //todo: activate print_warnings

    print_success("         Passed");
}


void gameMarkTest(){

    print_info("    Running Tests for marking a Pos as a Bomb ...");

    //todo:

    print_warning("         Test not implement ...");
}

void gameOpenTest(){

    print_info("    Running Tests for open a Pos ...");

    //todo:

    print_warning("         Test not implement ...");
}

void gameCapitulationTest(){

    print_info("    Running test for a capitulation in a game ...");

    //todo: deactivate print_errors

    game_startNew(4,4,1);
    game_capitulation();
    Pos pos = {.x = 0, .y = 0};
    assert(not game_mark(&pos));

    //todo: activate print_errors

    print_success("         Passed ...");
}

void destroyBoardTest(){

    print_info("    Running Tests for destroy a Board ...");

    //todo: deactivate print_errors

    game_startNew(4,4,1);
    destroyBoard();
    Pos pos = {.x = 1, .y = 2};
    assert(not game_mark(&pos));

    //todo: activate print_errors

    print_success("         Passed ...");
}

void gameTest(){

    print_info("Running Tests for game.c");

    gameWonTest();
    gameMarkTest();
    gameOpenTest();
    gameCapitulationTest();
    destroyBoardTest();
}