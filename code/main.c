/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "config.h"
#include "testSuite.h"

#include "event.h"

#include "mainTui.h"

int main(int argc, char *argv[]) {

    assert(argc == 1);

    runAllTests();

    mainTui();




//    print_debug("print_debug");
//    ifPrint_debug(false,"string %s", "true");
//    ifPrint_debug(true,"string %s", "false");


//    print_success("print_success");
//    print_info("print_info");
//    print_trace("print_trace");
//    print_debug("print_debug");
//    print_warning("print_warn");
//    print_error("print_error");
//    print_fatal("print_fatal");


    return EXIT_SUCCESS;
}
