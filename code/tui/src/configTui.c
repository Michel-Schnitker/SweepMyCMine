/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "configTui.h"

#include "globalTui.h"
#include "feature.h"
#include "string.h"
#include "event.h"

#define UP TUI_CONFIG_KEY_SELECT_UP
#define DOWN TUI_CONFIG_KEY_SELECT_DOWN
#define ENTER 10

#define SAVE TUI_CONFIG_KEY_SAVE
#define RESET TUI_CONFIG_KEY_RESET

static Features *config = null;

static uint32_t focusFeature = 0;


enum feature_names {
    OPEN_FIELD_AFTER_FINISH,
    FIRST_POS_IS_SAFE,
    USE_OPEN_HELPER,
    NON_FLAGGING,
    GAME_MODE,
    CUSTOMIZE_X_SIZE,
    CUSTOMIZE_Y_SIZE,
    CUSTOMIZE_BOMBS,
    USE_SOLVER_ALLOWED,
    MAX_FEATURES
};

static const char *feature_strings[] = {
        [OPEN_FIELD_AFTER_FINISH] = "Show Field after finish",
        [FIRST_POS_IS_SAFE] = "First Pos is a safe position",
        [USE_OPEN_HELPER] = "Use Helper for all Bombs marked",
        [NON_FLAGGING] = "No flags allowed",
        [GAME_MODE] = "Game Mode",
        [CUSTOMIZE_X_SIZE] = "   Custom field X Size",
        [CUSTOMIZE_Y_SIZE] = "   Custom field Y Size",
        [CUSTOMIZE_BOMBS] = "   Custom field bombs",
        [USE_SOLVER_ALLOWED] = "Use Solvers allowed",
};


void refreshConfig(){
    if(config != null)  free(config);
    config = getGameFeatures();
}

#define CONFIG_COMMENT_LENGTH 35
#define CONFIG_VALUE_LENGTH 10
#define CONFIG_TOTAL_TEXT_LENGTH (CONFIG_COMMENT_LENGTH + CONFIG_VALUE_LENGTH)


void printLine(uint32_t feature, uint32_t row, uint32_t windowCol, WINDOW *window){

    uint32_t col = (windowCol - CONFIG_TOTAL_TEXT_LENGTH) /2;

    if(feature == focusFeature){
        wattron(window, COLOR_PAIR(COLOR_MAIN_MENU));
    }
    else{
        wattron(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));
    }

    mvwprintw(window,row,col,"%s",feature_strings[feature]);

    wmove(window,row, col + CONFIG_COMMENT_LENGTH);

    switch (feature) {

        case OPEN_FIELD_AFTER_FINISH:
            wprintw(window, "%s",stringFromBool(config->openFieldAfterFinish));
            break;

        case FIRST_POS_IS_SAFE:
            wprintw(window, "%s",stringFromBool(config->startWithFirstSafePos));
            break;

        case USE_OPEN_HELPER:
            wprintw(window, "%s",stringFromBool(config->allBombsFoundAreaHelper));
            break;

        case NON_FLAGGING:
            wprintw(window, "%s",stringFromBool(config->nonFlagging));
            break;

        case GAME_MODE:
            wprintw(window, "%s",GameLevel_strings[config->gameMode]);
            break;

        case CUSTOMIZE_X_SIZE:
            //todo: Extra window for Number input
            wprintw(window, "%-3i", config->customizeFieldConfig.xSize);
            break;

        case CUSTOMIZE_Y_SIZE:
            //todo: Extra window for Number input
            wprintw(window, "%-3i", config->customizeFieldConfig.ySize);
            break;

        case CUSTOMIZE_BOMBS:
            //todo: Extra window for Number input
            wprintw(window, "%-3i", config->customizeFieldConfig.bombs);
            break;

        case USE_SOLVER_ALLOWED:
            wprintw(window, "%s",stringFromBool(config->solverAllowed));
            break;

        default:
            UNREACHABLE;
            break;
    }

}

void drawConfigWindow(uint32_t windowRow, uint32_t windowCol, WINDOW *window){

    uint32_t row = (windowRow - MAX_FEATURES) / 2;

    wbkgd(window,COLOR_PAIR(COLOR_MAIN_BACKGROUND));

    for (int i = 0; i < MAX_FEATURES; ++i) {

        printLine(i, row, windowCol, window);

        if(i == GAME_MODE and config->gameMode != GAME_LEVEL_CUSTOMIZE){
            i = CUSTOMIZE_BOMBS;
        }
        row++;
    }
}

void changeFeature(uint32_t feature){

    print_debug("change Feature");

    switch (feature) {

        case OPEN_FIELD_AFTER_FINISH:
            config->openFieldAfterFinish = config->openFieldAfterFinish ? false : true;
            break;

        case FIRST_POS_IS_SAFE:
            config->startWithFirstSafePos = config->startWithFirstSafePos ? false : true;
            break;

        case USE_OPEN_HELPER:
            config->allBombsFoundAreaHelper = config->allBombsFoundAreaHelper ? false : true;
            break;

        case NON_FLAGGING:
            config->nonFlagging = config->nonFlagging ? false : true;
            break;

        case GAME_MODE:
            config->gameMode = (config->gameMode + 1) % MAX_GAME_LEVELS;
            break;

        case CUSTOMIZE_X_SIZE:
            //todo: Extra window for Number input
            break;

        case CUSTOMIZE_Y_SIZE:
            //todo: Extra window for Number input
            break;

        case CUSTOMIZE_BOMBS:
            //todo: Extra window for Number input
            break;

        case USE_SOLVER_ALLOWED:
            config->solverAllowed = config->solverAllowed ? false : true;
            break;

        default:
            UNREACHABLE;
            break;
    }
}


void redirectInputToConfigWindow(int key){

    switch (key) {

        case SAVE:
            saveGameFeatures();
            break;

        case RESET:
            setDefaultFeatures();
            break;

        case UP:
            focusFeature = (focusFeature + MAX_FEATURES - 1) % MAX_FEATURES;
            if(focusFeature == CUSTOMIZE_BOMBS and config->gameMode != GAME_LEVEL_CUSTOMIZE){
                focusFeature = GAME_MODE;
            }
            break;

        case DOWN:
            focusFeature = (focusFeature + 1) % MAX_FEATURES;
            if(focusFeature == CUSTOMIZE_X_SIZE and config->gameMode != GAME_LEVEL_CUSTOMIZE){
                focusFeature = USE_SOLVER_ALLOWED;
            }
            break;

        case ENTER:
            changeFeature(focusFeature);
            break;

        default:
            break;
    }

}

void drawConfigStatusbar(WINDOW *window, int startCol){
    wmove(window,0, startCol);
    wbkgd(window,COLOR_PAIR(COLOR_MAIN_MENU));

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window,"(Esc)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Quit ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    wprintw(window,"(UP / DOWN)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Select ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    wprintw(window,"(ENTER)");
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Change ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    wprintw(window,"(%c)", SAVE);
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Save ");

    wattron(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    wprintw(window,"(%c)", RESET);
    wattroff(window,COLOR_PAIR(COLOR_MAIN_MENU_Akzent));
    waddstr(window," Reset ");
}

void openConfigWindow(){
    refreshConfig();
    focusFeature = 0;
}

void closeConfigWindow(){

    Features *oldConfig = getGameFeatures();

    if(memcmp(config, oldConfig, sizeof(Features)) != 0){
        setGameFeatures(config);
        game_startLevel(config->gameMode);
    }

    free(oldConfig);
}
