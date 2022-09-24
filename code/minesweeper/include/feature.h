/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef FEATURE_H_
#define FEATURE_H_

#include "types.h"
#include "game.h"
#include <stdlib.h>

//todo: implement allBombsFoundAreaHelper
//todo: implement solverAllowed

typedef struct Features {
    bool openFieldAfterFinish;
    bool startWithFirstSafePos;
    bool allBombsFoundAreaHelper;
    bool nonFlagging;
    _GameLevelConfig customizeFieldConfig;
    bool solverAllowed;
} Features;

void setDefaultFeatures();

Features* getGameFeatures();

bool setGameFeatures(Features *newFeatures);

void saveGameFeatures();

#endif //FEATURE_H_
