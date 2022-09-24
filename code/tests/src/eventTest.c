/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "eventTest.h"
#include "event.h"

void eventBufferTest(){

    print_info("    Running Tests buffer of events ...");

    startEventLogging(USE_LOG_BUFFER);

    print_success("print_success");
    print_info("print_info");
    print_trace("print_trace");
    print_debug("print_debug");
    print_warning("print_warn");
    print_error("print_error");

    uint32_t numOfEventBuffer = getEventBufferSize();

    startEventLogging(DIREKT_PRINT);

    ifPrint_fatal(numOfEventBuffer > 6, "         Buffer-size of events is to high.");
    ifPrint_fatal(numOfEventBuffer < 6, "         Buffer-size of events is to low.");
    ifPrint_fatal(getEventBufferSize() != 0, "         Buffer-size is already filled after restart logging.");

    print_warning("         Test not implement ...");
}

void eventFileOutTest(){

    print_info("    Running Tests for print events to file ...");

    //todo:

    print_warning("         Test not implement ...");
}

void eventDisableTest(){

    print_info("    Running Tests for disable EventLevels ...");

    startEventLogging(USE_LOG_BUFFER);
    disableEvent(EVENT_SUCCESS | EVENT_INFO | EVENT_TRACE | EVENT_DEBUG | EVENT_WARNING | EVENT_ERROR | EVENT_FATAL);

    print_success("print_success");
    print_info("print_info");
    print_trace("print_trace");
    print_debug("print_debug");
    print_warning("print_warn");
    print_error("print_error");
    print_fatal("print_fatal");

    uint32_t numOfEventBuffer = getEventBufferSize();

    startEventLogging(DIREKT_PRINT);

    ifPrint_fatal(numOfEventBuffer != 0, "         Buffer-size of events is not zero but all events are disabled.");

    print_warning("         Test not implement ...");
}

void eventTest(){

    print_info("Running Tests for event");

    enableEvent(EVENT_SUCCESS | EVENT_INFO | EVENT_TRACE | EVENT_DEBUG | EVENT_WARNING | EVENT_ERROR | EVENT_FATAL);

    eventBufferTest();
    eventFileOutTest();
    eventDisableTest();

    setDefaultEnableEvent();
}
