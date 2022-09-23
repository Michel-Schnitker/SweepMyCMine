/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define BOARD_MAXSIZE_X 90
#define BOARD_MAXSIZE_Y 90
#define BOARD_MINSIZE_X 4
#define BOARD_MINSIZE_Y 4

#define BOARD_SIGN_MARKASBOMB "P"
#define BOARD_SIGN_WRONGMARKER "X"
#define BOARD_SIGN_CONCEALED "?"
#define BOARD_SIGN_BOMB "B"
#define BOARD_SIGN_EMPTY " "

#define GAME_LEVEL_BEGINNER_SIZE_X 9
#define GAME_LEVEL_BEGINNER_SIZE_Y 9
#define GAME_LEVEL_BEGINNER_BOMBS 10
#define GAME_LEVEL_INTERMEDIATE_SIZE_X 16
#define GAME_LEVEL_INTERMEDIATE_SIZE_Y 16
#define GAME_LEVEL_INTERMEDIATE_BOMBS 40
#define GAME_LEVEL_EXPERT_SIZE_X 30
#define GAME_LEVEL_EXPERT_SIZE_Y 16
#define GAME_LEVEL_EXPERT_BOMBS 99

#define DEBUGMODE false

//todo: transfer Configuration
#define OPEN_FIELD_AFTER_FINISH true
#define START_WITH_FIRST_SAFE_POS true
#define ALL_BOMBS_FOUND_AREA_HELPER false       // todo: implement
#define NON_FLAGGING false                           // todo: implement

#define TUI_GAME_KEY_UP KEY_UP
#define TUI_GAME_KEY_DOWN KEY_DOWN
#define TUI_GAME_KEY_LEFT KEY_LEFT
#define TUI_GAME_KEY_RIGHT KEY_RIGHT
#define TUI_GAME_KEY_OPEN 'e'
#define TUI_GAME_KEY_MARK 'w'
#define TUI_GAME_KEY_CAPITULATION 'q'
#define TUI_GAME_KEY_HELPER 't'
#define TUI_GAME_KEY_SOLVER 'z'

#define TUI_COLOR_BACKGROUND COLOR_BLACK
#define TUI_COLOR_FRONT_TEXT COLOR_WHITE
#define TUI_COLOR_FRONT_AKZENT_TEXT COLOR_BLACK
#define TUI_COLOR_FRONT_GAME_NUMBER COLOR_YELLOW
#define TUI_COLOR_FRONT_GAME_MARKER COLOR_BLUE
#define TUI_COLOR_FRONT_GAME_WRONG_MARKER COLOR_MAGENTA
#define TUI_COLOR_FRONT_GAME_BOMB COLOR_RED
#define TUI_COLOR_FRONT_GAME_CURSOR COLOR_GREEN

#define EVENT_MAX_AMOUNT_LOGGING 10             //todo search and fix the Bug
#define EVENT_LOGGING_PATH "logging.txt"

#define SCORE_FILE_PATH ".score"
#define FEATURE_FILE_PATH ".config"

#endif  // CONFIG_H_
