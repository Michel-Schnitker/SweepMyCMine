/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "featuresTest.h"
#include "feature.h"
#include "event.h"

void defaultFeaturesTest(){

    print_info("    Running Tests for default feature ...");

    setDefaultFeatures();

    Features *features = getGameFeatures();

    ifPrint_fatal(features->openFieldAfterFinish != FEATURE_DEFAULT_openFieldAfterFinish, "         wrong openFieldAfterFinish value");
    ifPrint_fatal(features->startWithFirstSafePos != FEATURE_DEFAULT_startWithFirstSafePos, "         wrong startWithFirstSafePos value");
    ifPrint_fatal(features->allBombsFoundAreaHelper != FEATURE_DEFAULT_allBombsFoundAreaHelper, "         wrong allBombsFoundAreaHelper value");
    ifPrint_fatal(features->nonFlagging != FEATURE_DEFAULT_nonFlagging, "         wrong nonFlagging value");
    ifPrint_fatal(features->customizeFieldConfig.xSize != FEATURE_DEFAULT_customizeFieldConfig_xSize, "         wrong FEATURE_DEFAULT_customizeFieldConfig_xSize value");
    ifPrint_fatal(features->customizeFieldConfig.ySize != FEATURE_DEFAULT_customizeFieldConfig_ySize, "         wrong FEATURE_DEFAULT_customizeFieldConfig_ySize value");
    ifPrint_fatal(features->customizeFieldConfig.bombs != FEATURE_DEFAULT_customizeFieldConfig_bombs, "         wrong FEATURE_DEFAULT_customizeFieldConfig_bombs value");
    ifPrint_fatal(features->solverAllowed != FEATURE_DEFAULT_solverAllowed, "         wrong solverAllowed value");

    free(features);

    print_success("         Passed");
}

void changeFeatureTest(){

    print_info("    Running Tests for change feature ...");

    setDefaultFeatures();

    Features *features = getGameFeatures();

    ifPrint_fatal(setGameFeatures(features), "         return value is true but the features has no difference");
    features->openFieldAfterFinish = not FEATURE_DEFAULT_openFieldAfterFinish;
    ifPrint_fatal(not setGameFeatures(features), "         return value is false but the features are different");

    free(features);

    print_success("         Passed");
}

void featuresTest(){

    print_info("Running Tests for feature.c");

    defaultFeaturesTest();
    changeFeatureTest();

    setDefaultFeatures();
}
