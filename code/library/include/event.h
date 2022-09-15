/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <stdarg.h>
#include <time.h>
#include <stdio.h>

#include "config.h"
#include "types.h"

#define EVENT_COLORING true
#define EVENT_STREAM stdout // stderr, stdout or file
#define EVENT_MESSAGE_LENGTH_META 23
#define EVENT_MESSAGE_LENGTH_PATH 149
#define EVENT_MESSAGE_LENGTH_MSG 149

#define EVENT_SUCCESS_ENABLE_DEFAULT true
#define EVENT_INFO_ENABLE_DEFAULT true
#define EVENT_TRACE_ENABLE_DEFAULT true
#define EVENT_DEBUG_ENABLE_DEFAULT true
#define EVENT_WARNING_ENABLE_DEFAULT true
#define EVENT_ERROR_ENABLE_DEFAULT true
#define EVENT_FATAL_ENABLE_DEFAULT true

//todo: make event thread safe

//todo: implement IF-Print for debugging and a slim code

enum eventLevel {
    EVENT_SUCCESS = (1<<0),
    EVENT_INFO = (1<<1),
    EVENT_TRACE = (1<<2),
    EVENT_DEBUG = (1<<3),
    EVENT_WARNING = (1<<4),
    EVENT_ERROR = (1<<5),
    EVENT_FATAL = (1<<6),
    NUM_OF_LEVELS
};

typedef struct {
    enum eventLevel level;
    char *metaString;
    char *pathString;
    char *messageString;
} EventElement;

enum loggingMode {
    DIREKT_PRINT = (1<<0),
    PRINT_TO_FILE = (1<<1),
    USE_LOG_BUFFER = (1<<2),
};


void startEventLogging(enum loggingMode mode);

void stopEventLogging();

EventElement* getEventMessageFromLog();

uint32_t getEventBufferSize();

#define ifPrint_success(b, ...) printEvent(EVENT_SUCCESS, __FILE__, __LINE__, __func__, b, __VA_ARGS__)
#define ifPrint_info(b, ...)  printEvent(EVENT_INFO,  __FILE__, __LINE__, __func__, b, __VA_ARGS__)
#define ifPrint_trace(b, ...) printEvent(EVENT_TRACE, __FILE__, __LINE__, __func__, b, __VA_ARGS__)
#define ifPrint_debug(b, ...) printEvent(EVENT_DEBUG, __FILE__, __LINE__, __func__, b, __VA_ARGS__)
#define ifPrint_warning(b, ...)  printEvent(EVENT_WARNING,  __FILE__, __LINE__, __func__, b, __VA_ARGS__)
#define ifPrint_error(b, ...) printEvent(EVENT_ERROR, __FILE__, __LINE__, __func__, b, __VA_ARGS__)
#define ifPrint_fatal(b, ...) printEvent(EVENT_FATAL, __FILE__, __LINE__, __func__, b, __VA_ARGS__)

#define print_success(...) printEvent(EVENT_SUCCESS, __FILE__, __LINE__, __func__, true, __VA_ARGS__)
#define print_info(...)  printEvent(EVENT_INFO,  __FILE__, __LINE__, __func__, true, __VA_ARGS__)
#define print_trace(...) printEvent(EVENT_TRACE, __FILE__, __LINE__, __func__, true, __VA_ARGS__)
#define print_debug(...) printEvent(EVENT_DEBUG, __FILE__, __LINE__, __func__, true, __VA_ARGS__)
#define print_warning(...)  printEvent(EVENT_WARNING,  __FILE__, __LINE__, __func__, true, __VA_ARGS__)
#define print_error(...) printEvent(EVENT_ERROR, __FILE__, __LINE__, __func__, true, __VA_ARGS__)
#define print_fatal(...) printEvent(EVENT_FATAL, __FILE__, __LINE__, __func__, true, __VA_ARGS__)

void printEvent(enum eventLevel level, const char *file, int line, const char *func, bool ifBool, const char *fmt, ...);





void enableEvent(enum eventLevel level);

void disableEvent(enum eventLevel level);

#endif  // EVENT_H_
