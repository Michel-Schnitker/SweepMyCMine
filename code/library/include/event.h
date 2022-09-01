
#ifndef EVENT_H_
#define EVENT_H_

#include <stdarg.h>
#include <time.h>
#include <stdio.h>

#include "types.h"

#define EVENT_COLORING true
#define EVENT_STREAM stdout // stderr, stdout or file

#define EVENT_SUCCESS_ENABLE_DEFAULT true
#define EVENT_INFO_ENABLE_DEFAULT true
#define EVENT_TRACE_ENABLE_DEFAULT true
#define EVENT_DEBUG_ENABLE_DEFAULT true
#define EVENT_WARNING_ENABLE_DEFAULT true
#define EVENT_ERROR_ENABLE_DEFAULT true
#define EVENT_FATAL_ENABLE_DEFAULT true

//todo: include Liste for Event-logging
//todo:     -> enables log data export to a file
//todo: make event thread safe
//todo: define variable array for printing addon time and path

typedef struct {
    va_list ap;
    const char *fmt;
    const char *file;
    const char *func;
    struct tm *time;
    void *udata;
    int line;
    int level;
} eventElement;

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



#define print_success(...) printEvent(EVENT_SUCCESS, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_info(...)  printEvent(EVENT_INFO,  __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_trace(...) printEvent(EVENT_TRACE, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_debug(...) printEvent(EVENT_DEBUG, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_warning(...)  printEvent(EVENT_WARNING,  __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_error(...) printEvent(EVENT_ERROR, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_fatal(...) printEvent(EVENT_FATAL, __FILE__, __LINE__, __func__, __VA_ARGS__)


void printEvent(int level, const char *file, int line, const char *func, const char *fmt, ...);

void enableEvent(enum eventLevel level);

void disableEvent(enum eventLevel level);

#endif  // EVENT_H_
