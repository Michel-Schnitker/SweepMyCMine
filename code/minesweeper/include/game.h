/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef GAME_H_
#define GAME_H_

#include <time.h>

#include "config.h"
#include "types.h"
#include "board.h"
#include "pos.h"

//todo: wrap in own thread

enum GameLevel {
    GAME_LEVEL_CUSTOMIZE,
    GAME_LEVEL_BEGINNER,
    GAME_LEVEL_INTERMEDIATE,
    GAME_LEVEL_EXPERT,
    MAX_GAME_LEVELS,
};

static const char *GameLevel_strings[] = {
        [GAME_LEVEL_CUSTOMIZE] = "Customize",
        [GAME_LEVEL_BEGINNER] = "Beginner",
        [GAME_LEVEL_INTERMEDIATE] = "Intermediate",
        [GAME_LEVEL_EXPERT] = "Expert",
};

typedef struct _GameLevelConfig {
    uint32_t xSize;
    uint32_t ySize;
    uint32_t bombs;
} _GameLevelConfig;

static const _GameLevelConfig GameLevelConfig[] = {
        [GAME_LEVEL_CUSTOMIZE] = {.xSize = 0,
                                  .ySize = 0,
                                  .bombs = 0},
        [GAME_LEVEL_BEGINNER] = {.xSize = GAME_LEVEL_BEGINNER_SIZE_X,
                                 .ySize = GAME_LEVEL_BEGINNER_SIZE_Y,
                                 .bombs = GAME_LEVEL_BEGINNER_BOMBS},
        [GAME_LEVEL_INTERMEDIATE] = {.xSize = GAME_LEVEL_INTERMEDIATE_SIZE_X,
                                     .ySize = GAME_LEVEL_INTERMEDIATE_SIZE_Y,
                                     .bombs = GAME_LEVEL_INTERMEDIATE_BOMBS},
        [GAME_LEVEL_EXPERT] = {.xSize = GAME_LEVEL_EXPERT_SIZE_X,
                               .ySize = GAME_LEVEL_EXPERT_SIZE_Y,
                               .bombs = GAME_LEVEL_EXPERT_BOMBS},
};

enum CellState {
    CELL_EMPTY = 0,
    CELL_BOMB_IN_AREA_ONE = 1,
    CELL_BOMB_IN_AREA_TWO = 2,
    CELL_BOMB_IN_AREA_THREE = 3,
    CELL_BOMB_IN_AREA_FOUR = 4,
    CELL_BOMB_IN_AREA_FIVE = 5,
    CELL_BOMB_IN_AREA_SIX = 6,
    CELL_BOMB_IN_AREA_SEVEN = 7,
    CELL_BOMB_IN_AREA_EIGHT = 8,
    CELL_BOMB_INSIDE = 9,
    CELL_CONCEALED = 10,
    CELL_MARKED_AS_BOMB = 11,
    CELL_WRONG_MARK_AS_BOMB = 12,
};

typedef struct GameBoard {
    uint32_t xSize;
    uint32_t ySize;
    int32_t cellsToBeFound;

    enum CellState ** field;

    bool gameStarted;
    bool gameFinish;
    bool gameWon;

    time_t runtime;
    enum GameLevel gameLevel;

    void (*free)(struct GameBoard *gameBoard);
    bool (*validPos)(struct Pos *pos);
} GameBoard;

void game_startLevel(enum GameLevel level);

void game_startCustomize(uint32_t xSize, uint32_t ySize, uint32_t bombs);

void game_restart();

bool game_startThis(Board *board);

bool game_mark(Pos * pos);

bool game_open(Pos * pos);

void game_capitulation();

void destroyBoard();

GameBoard * getGameBoard();

enum GameLevel getCurrentGameLevel();


#endif //GAME_H_
