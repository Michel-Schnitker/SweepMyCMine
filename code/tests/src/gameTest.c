
#include "config.h"
#include "gameTest.h"
#include "game.h"
#include "pos.h"
#include "event.h"
#include "random.h"

void gameWonTest(){

    print_info("    Running Tests for win a game ...");

#if START_WITH_FIRST_SAFE_POS
    // FirstPos is required so that the playing field is not recreated with mode FIRST_SAFE_POS. Otherwise the locations of the bombs would be unknown.
    Pos pos1 = {.x = 0, .y = 0};
    Board *board = constructRandBoardWithBombproofPos(5,5,2,&pos1);

#else
    Board *board = constructFullyRandomBoard(5,5,2);

#endif

    game_startThis(board);

    assert(board->gameFinish == false);
    assert(board->gameStarted == false);
    assert(board->openCells == 0);
    assert(board->xSize == 5 and board->ySize == 5 and board->bombs == 2);

    disableEvent(EVENT_WARNING | EVENT_INFO);
    for (uint32_t y = 0; y < board->ySize; ++y) {
        for (uint32_t x = 0; x < board->xSize; ++x) {

            if(board->gameFinish){ break;}

            if(not board->field[y][x].containsBomb and board->field[y][x].concealed){
                Pos pos = {.x = x, .y = y};
                game_open(&pos);
            }
        }
    }
    enableEvent(EVENT_WARNING | EVENT_INFO);

    assert(board->gameStarted == true);
    assert(board->gameFinish == true);
    assert(board->gameWon == true);
    assert(board->bombs == 25 - board->openCells);

    print_success("         Passed");
}


void gameMarkTest(){

    print_info("    Running Tests for marking a Pos as a Bomb ...");

    Board *board = constructFullyRandomBoard(5,5,2);
    game_startThis(board);

    assert(board->gameFinish == false);
    assert(board->gameStarted == false);
    assert(board->openCells == 0);
    assert(board->bombMarkers == 0);
    assert(board->xSize == 5 and board->ySize == 5 and board->bombs == 2);

    int32_t randomX = getRandomInRange(0,board->xSize-1), randomY = getRandomInRange(0,board->ySize-1);

    Cell *randomCell = &(board->field[randomY][randomX]);
    Pos randomPos = {.x = randomX, .y = randomY};

    assert(not randomCell->markedAsBomb);
    assert(game_mark(&randomPos));
    assert(board->bombMarkers == 1);
    assert(board->openCells == 0);
    assert(randomCell->markedAsBomb);
    assert(game_mark(&randomPos));
    assert(board->bombMarkers == 0);
    assert(not randomCell->markedAsBomb);

    assert(board->gameStarted == true);
    assert(board->gameFinish == false);
    assert(board->gameWon == false);
    assert(board->openCells == 0);

    print_success("         Passed");
}

void gameOpenTest(){

    print_info("    Running Tests for open a Pos ...");

#if START_WITH_FIRST_SAFE_POS
    // FirstPos is required so that the playing field is not recreated with mode FIRST_SAFE_POS. Otherwise the locations of the bombs would be unknown.
    Pos randomPos = {.x = 2, .y = 3};
    Board *board = constructRandBoardWithBombproofPos(5,5,13,&randomPos);
    Cell *randomCell = &(board->field[randomPos.x][randomPos.y]);

#else
    Board *board = constructFullyRandomBoard(5,5,13);

    int32_t randomX = getRandomInRange(0,board->xSize-1), randomY = getRandomInRange(0,board->ySize-1);

    Cell *randomCell = &(board->field[randomY][randomX]);
    Pos randomPos = {.x = randomX, .y = randomY};

#endif

    game_startThis(board);

    assert(board->gameFinish == false);
    assert(board->gameStarted == false);
    assert(board->openCells == 0);
    assert(board->xSize == 5 and board->ySize == 5 and board->bombs == 13);

    disableEvent(EVENT_INFO);
    assert(randomCell->concealed);
    assert(game_open(&randomPos));
    assert(not randomCell->concealed);

    assert(board->openCells > 0);
    assert(board->gameStarted == true);


    disableEvent(EVENT_ERROR | EVENT_WARNING);
    assert(not game_open(&randomPos));
    enableEvent(EVENT_ERROR | EVENT_WARNING | EVENT_INFO);
    assert(not randomCell->concealed);

    assert(board->openCells > 0);
    assert(board->gameStarted == true);

    print_success("         Passed");
}

void gameCapitulationTest(){

    print_info("    Running test for a capitulation in a game ...");

    game_startNew(4,4,1);
    game_capitulation();
    Pos pos = {.x = 0, .y = 0};

    disableEvent(EVENT_ERROR);
    assert(not game_mark(&pos));
    enableEvent(EVENT_ERROR);

    print_success("         Passed");
}

void destroyBoardTest(){

    print_info("    Running Tests for destroy a Board ...");

    game_startNew(4,4,1);
    destroyBoard();
    Pos pos = {.x = 1, .y = 2};

    disableEvent(EVENT_ERROR);
    assert(not game_mark(&pos));
    enableEvent(EVENT_ERROR);

    print_success("         Passed");
}

void getGameBoardMarkTest(){

    print_info("    Running Tests for get a GameBoard after mark a Cell ...");

    game_startNew(9,10,10);

    GameBoard * board = getGameBoard();

    assert(board->xSize == 9 and board->ySize == 10);
    assert(board->cellsToBeFound == 10);
    assert(board->gameStarted == false and board->gameFinish == false and board->gameWon == false);
    assert(board->free != null);

    int32_t randomX = getRandomInRange(0,8), randomY = getRandomInRange(0,9);
    Pos randomPos = {.x = randomX, .y = randomY};

    game_mark(&randomPos);

    board->free(board);
    board = getGameBoard();

    assert(board->xSize == 9 and board->ySize == 10);
    assert(board->cellsToBeFound == 9);
    assert(board->gameStarted == true and board->gameFinish == false and board->gameWon == false);
    assert(board->free != null);

    game_mark(&randomPos);

    board->free(board);
    board = getGameBoard();

    assert(board->xSize == 9 and board->ySize == 10);
    assert(board->cellsToBeFound == 10);
    assert(board->gameStarted == true and board->gameFinish == false and board->gameWon == false);
    assert(board->free != null);

    board->free(board);

    print_success("         Passed");
}

void getGameBoardOpenTest(){

    print_info("    Running Tests for get a GameBoard after open a Cell ...");

    game_startNew(9,10,10);

    GameBoard * board = getGameBoard();

    assert(board->xSize == 9 and board->ySize == 10);
    assert(board->cellsToBeFound == 10);
    assert(board->gameStarted == false and board->gameFinish == false and board->gameWon == false);
    assert(board->free != null);

    int32_t randomX = getRandomInRange(0,8), randomY = getRandomInRange(0,9);
    Pos randomPos = {.x = randomX, .y = randomY};

    game_open(&randomPos);

    board->free(board);
    board = getGameBoard();

    assert(board->xSize == 9 and board->ySize == 10);
    assert(board->cellsToBeFound == 10);
    assert(board->gameStarted == true);
    assert(board->free != null);

    board->free(board);

    print_success("         Passed");
}

void gameTest(){

    print_info("Running Tests for game.c");

    gameWonTest();
    gameMarkTest();
    gameOpenTest();
    gameCapitulationTest();
    destroyBoardTest();
    getGameBoardMarkTest();
    getGameBoardOpenTest();

    destroyBoard();
}