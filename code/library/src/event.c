#include "event.h"

static const char *level_strings[] = {
        [EVENT_SUCCESS] = "SUCCESS",
        [EVENT_INFO] = "INFO",
        [EVENT_TRACE] = "TRACE",
        [EVENT_DEBUG] = "DEBUG",
        [EVENT_WARNING] = "WARNING",
        [EVENT_ERROR] = "ERROR",
        [EVENT_FATAL] = "FATAL",
};

#if EVENT_COLORING

static const char *level_colors[] = {
        [EVENT_SUCCESS] = "\x1b[32m",
        [EVENT_INFO] = "\x1b[37m",
        [EVENT_TRACE] = "\x1b[34m",
        [EVENT_DEBUG] = "\x1b[36m",
        [EVENT_WARNING] = "\x1b[33m",
        [EVENT_ERROR] = "\x1b[31m",
        [EVENT_FATAL] = "\x1b[35m",
};

#endif


static void printEventElement(eventElement *event) {
    char timeStamp[16];
    timeStamp[strftime(timeStamp, sizeof(timeStamp), "%H:%M:%S", event->time)] = '\0';

#if EVENT_COLORING

    fprintf(
            event->udata,
            "%s%-7s %s\x1b[0m \x1b[90m%s:%d -> %s() :\x1b[0m ",
            level_colors[event->level],
            level_strings[event->level],
            timeStamp,
            event->file,
            event->line,
            event->func);

    fprintf(event->udata, "%s",level_colors[event->level]);
#else

    fprintf(
            event->udata,
            "%-7s %s  %s:%d -> %s() : ",
            level_strings[event->level],
            timeStamp,
            event->file,
            event->line,
            event->func);

#endif

    vfprintf(event->udata, event->fmt, event->ap);

#if EVENT_COLORING
    fprintf(event->udata, "\x1b[0m");
#endif

    fprintf(event->udata, "\n");
    fflush(event->udata);
}


void printEvent(int level, const char *file, int line, const char *func, const char *fmt, ...) {

    eventElement ev = {
            .fmt   = fmt,
            .file  = file,
            .line  = line,
            .func  = func,
            .level = level,
    };

    if (!ev.time) {
        time_t t = time(NULL);
        ev.time = localtime(&t);
    }

    ev.udata = EVENT_STREAM;

    va_start(ev.ap, fmt);
    printEventElement(&ev);
    va_end(ev.ap);
}