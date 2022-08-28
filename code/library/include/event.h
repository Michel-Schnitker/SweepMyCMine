#ifndef EVENT_H_
#define EVENT_H_

#include <types.h>
#include <stdarg.h>
#include <time.h>
#include <stdio.h>

#define EVENT_COLORING true
#define EVENT_STREAM stdout // stderr, stdout or file

//todo: include a array for muting of the different Event Levels
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
    EVENT_SUCCESS,
    EVENT_INFO,
    EVENT_TRACE,
    EVENT_DEBUG,
    EVENT_WARNING,
    EVENT_ERROR,
    EVENT_FATAL,
};

#define print_success(...) printEvent(EVENT_SUCCESS, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_info(...)  printEvent(EVENT_INFO,  __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_trace(...) printEvent(EVENT_TRACE, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_debug(...) printEvent(EVENT_DEBUG, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_warning(...)  printEvent(EVENT_WARNING,  __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_error(...) printEvent(EVENT_ERROR, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define print_fatal(...) printEvent(EVENT_FATAL, __FILE__, __LINE__, __func__, __VA_ARGS__)


void printEvent(int level, const char *file, int line, const char *func, const char *fmt, ...);


#endif  // EVENT_H_
