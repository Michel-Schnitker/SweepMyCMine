/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "event.h"


#include "stdlib.h"
#include "string.h"

#include "config.h"
#include "types.h"
#include "list.h"

#define COUNT_LEVELS 7

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

static bool levelEnable[NUM_OF_LEVELS] = {
        [EVENT_SUCCESS] = EVENT_SUCCESS_ENABLE_DEFAULT,
        [EVENT_INFO] = EVENT_INFO_ENABLE_DEFAULT,
        [EVENT_TRACE] = EVENT_TRACE_ENABLE_DEFAULT,
        [EVENT_DEBUG] = EVENT_DEBUG_ENABLE_DEFAULT,
        [EVENT_WARNING] = EVENT_WARNING_ENABLE_DEFAULT,
        [EVENT_ERROR] = EVENT_ERROR_ENABLE_DEFAULT,
        [EVENT_FATAL] = EVENT_FATAL_ENABLE_DEFAULT,
};


EventElement *new_EventElem(){
    EventElement *event = calloc(1, sizeof(EventElement) );
    event->metaString = calloc(EVENT_MESSAGE_LENGTH_META + 1, sizeof(char) );
    event->pathString = calloc(EVENT_MESSAGE_LENGTH_PATH + 1, sizeof(char) );
    event->messageString = calloc(EVENT_MESSAGE_LENGTH_MSG + 1, sizeof(char) );

    return event;
}

void freeEventElem(EventElement *event){
    free(event->metaString);
    free(event->pathString);
    free(event->messageString);
    free(event);
}


static void *eventPrintOut = null;
static FILE *eventFileOut = null;

static List *eventBufferList = null;
static uint32_t messageBufferReturnCounter = 0;

void stopEventLogging(){

    eventPrintOut = null;

    if(eventFileOut != null) fclose(eventFileOut);
    eventFileOut = null;

    if(eventBufferList != null) eventBufferList->delete(eventBufferList, (void*) freeEventElem);
    eventBufferList = null;
}

void startEventLogging(enum loggingMode mode){

    stopEventLogging();

    if(mode & DIREKT_PRINT){

        eventPrintOut = EVENT_STREAM;
    }

    if(mode & PRINT_TO_FILE){

        eventFileOut = fopen(EVENT_LOGGING_PATH, "a+");
        if (eventFileOut == null) print_fatal("Could not open file: %s", EVENT_LOGGING_PATH);
    }

    if(mode & USE_LOG_BUFFER){

        eventBufferList = new_List();
        messageBufferReturnCounter = 0;
    }

}

EventElement* getEventMessageFromLog(){
    if(eventBufferList == null) return null;

    if(messageBufferReturnCounter >= eventBufferList->size){
        messageBufferReturnCounter = 0;
        return null;
    }

    EventElement* msg = eventBufferList->getIndex(eventBufferList, messageBufferReturnCounter);
    messageBufferReturnCounter++;

    return msg;
}

uint32_t getEventBufferSize(){
    if(eventBufferList == null){
        return 0;
    }
    else{
        return eventBufferList->size;
    }
}


void printEventToFile(FILE *stream, EventElement *event){

#if EVENT_COLORING

    fprintf(stream,
            "%s%s\x1b[0m \x1b[90m%s :\x1b[0m %s%s \x1b[0m \n",
            level_colors[event->level],
            event->metaString,
            event->pathString,
            level_colors[event->level],
            event->messageString);

#else

    fprintf(stream,
            "%s %s : %s \n",
            event->metaString,
            event->pathString,
            event->messageString);

#endif

    fflush(stream);
}


void printEvent(enum eventLevel level, const char *file, int line, const char *func, const char *fmt, ...) {

    if(not levelEnable[level]) return;


    EventElement *event = new_EventElem();

    event->level = level;

    char timeStamp[16];
    time_t t = time(null);
    timeStamp[strftime(timeStamp, sizeof(timeStamp), "%H:%M:%S", localtime(&t))] = '\0';

    snprintf(event->metaString,
             EVENT_MESSAGE_LENGTH_META,
             "%-7s %s ",
             level_strings[event->level],
             timeStamp);

    snprintf(event->pathString,
             EVENT_MESSAGE_LENGTH_PATH,
             "%s:%d -> %s() ",
             file,
             line,
             func);

    va_list args;
    va_start(args, fmt);
    vsnprintf(event->messageString,
              EVENT_MESSAGE_LENGTH_MSG,
              fmt,
              args);
    va_end(args);


    if(eventPrintOut != null){
        printEventToFile(eventPrintOut, event);
    }

    if(eventFileOut != null){
        printEventToFile(eventFileOut, event);
    }

    if(eventBufferList != null){

        messageBufferReturnCounter = 0;

        if(eventBufferList->size >= EVENT_MAX_AMOUNT_LOGGING){
            EventElement *oldMsg = eventBufferList->popFirst(eventBufferList);
            freeEventElem(oldMsg);
        }
        eventBufferList->add(eventBufferList, event);
    }
    else{
        freeEventElem(event);
    }

    if(level == EVENT_FATAL){
        stopEventLogging();
        UNREACHABLE;
    }
}


void setEnableingForEvents(enum eventLevel level, bool req){
    for (int i = 0; i < COUNT_LEVELS; ++i) {
        if(level & (1<<0)){
            levelEnable[(1<<i)] = req;
        }
        level = level >> 1;
    }
}

void enableEvent(enum eventLevel level){
    setEnableingForEvents(level, true);
}

void disableEvent(enum eventLevel level){
    setEnableingForEvents(level, false);
}
