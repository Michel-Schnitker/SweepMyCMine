/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "feature.h"
#include <string.h>

static Features *currentFeatures = null;

void _createNewFeatures(){
    currentFeatures = calloc(1, sizeof(Features));
}

void setDefaultFeatures(){
    if(currentFeatures == null){
        _createNewFeatures();
    }

    currentFeatures->openFieldAfterFinish = FEATURE_DEFAULT_openFieldAfterFinish;
    currentFeatures->startWithFirstSafePos = FEATURE_DEFAULT_startWithFirstSafePos;
    currentFeatures->allBombsFoundAreaHelper = FEATURE_DEFAULT_allBombsFoundAreaHelper;
    currentFeatures->nonFlagging = FEATURE_DEFAULT_nonFlagging;
    currentFeatures->customizeFieldConfig.xSize = FEATURE_DEFAULT_customizeFieldConfig_xSize;
    currentFeatures->customizeFieldConfig.ySize = FEATURE_DEFAULT_customizeFieldConfig_ySize;
    currentFeatures->customizeFieldConfig.bombs = FEATURE_DEFAULT_customizeFieldConfig_bombs;
    currentFeatures->gameMode = FEATURE_DEFAULT_gameMode;
    currentFeatures->solverAllowed = FEATURE_DEFAULT_solverAllowed;
}

Features* _cloneFeatures(){

    assert(currentFeatures != null);
    Features *cloneFeatures = calloc(1, sizeof(Features));

    memcpy(cloneFeatures, currentFeatures, sizeof(Features) );

    return cloneFeatures;
}

void _loadGameFeatures(){
    //todo:
    setDefaultFeatures(); //todo: Bypass while _loadGameFeatures() is not implemented
}

Features* getGameFeatures(){

    if(currentFeatures == null){
        _loadGameFeatures();
    }

    return _cloneFeatures();
}

bool setGameFeatures(Features *newFeatures){

    if(currentFeatures == null){
        _createNewFeatures();
    }

    if(memcmp(currentFeatures, newFeatures, sizeof(Features)) == 0){
        return false;
    }

    memcpy(currentFeatures, newFeatures, sizeof(Features) );

    game_restart();

    return true;
}

void saveGameFeatures(){
    //todo:
}
