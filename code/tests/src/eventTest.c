/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "eventTest.h"
#include "event.h"

//todo: exchange from assert to ifPrint_Fatal

void eventBufferTest(){

    print_info("    Running Tests buffer of events ...");

    //todo:

    print_warning("         Test not implement ...");
}

void eventFileOutTest(){

    print_info("    Running Tests for print events to file ...");

    //todo:

    print_warning("         Test not implement ...");
}

void eventDisableTest(){

    print_info("    Running Tests for disable EventLevels ...");

    //todo:

    print_warning("         Test not implement ...");
}

void eventTest(){

    print_info("Running Tests for event");

    eventBufferTest();
    eventFileOutTest();
    eventDisableTest();
}