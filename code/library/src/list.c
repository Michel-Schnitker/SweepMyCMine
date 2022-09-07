/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "list.h"

#include <stdlib.h>
#include "event.h"

void add(List *list, void *payload) {
    nonNull(list);
    nonNull(payload);

    ListElement *newElem = calloc(1, sizeof(ListElement));
    nonNull(newElem);
    newElem->payload = payload;

    if (list->size == 0) {

        list->_head = newElem;
        list->_tail = newElem;
    }
    else {

        list->_tail->next = newElem;
        newElem->prev = list->_tail;
        list->_tail = newElem;
    }

    list->size++;
}

// Element must be on this list, but this is guaranteed because this function is only called from this list.
void unhookElement(List *list, ListElement *elem){
    nonNull(list);
    assert(list->size > 0);
    nonNull(elem);

    if (list->size == 1){

        list->_head = null;
        list->_tail = null;
    }
    else{

        if (elem->prev == null){

            list->_head = elem->next;
            elem->next->prev = null;
        }
        else if(elem->next == null){

            list->_tail = null;
            elem->prev->next = null;
        }
        else{

            elem->next->prev = elem->prev;
            elem->prev->next = elem->next;
        }
    }

    list->size--;
    free(elem);
}


ListElement *getListElementFromCompare(List *list, void *payload, bool (*compareElemFunc)(void *payloadOne, void *payloadTwo)){
    nonNull(list);
    nonNull(payload);
    nonNull(compareElemFunc);

    for (ListElement *current = list->_head; current != NULL; current = current->next) {
        if(compareElemFunc(current->payload, payload)){
            return current;
        }
    }
    return null;
}


ListElement *getListElementFromPayloadPointer(List *list, void *payload){
    nonNull(list);
    nonNull(payload);

    for (ListElement *current = list->_head; current != NULL; current = current->next) {
        if(current->payload == payload){
            return current;
        }
    }
    return null;
}


void removeElem(List *list, void *payload, bool (*compareElemFunc)(void *payloadOne, void *payloadTwo), void (*deleteElemFunc)(void *payload)) {
    nonNull(list);
    nonNull(payload);

    ListElement *current = null;

    if(compareElemFunc == null){
        current = getListElementFromPayloadPointer(list, payload);
    }
    else{
        current = getListElementFromCompare(list, payload, compareElemFunc);
    }

    if (current == null){return;}
    if(deleteElemFunc != null){deleteElemFunc(current->payload);}
    unhookElement(list, current);
}


ListElement *getListElementFromIndex(List *list, uint32_t index){
    nonNull(list);
    assert(index < list->size);

    ListElement *current = list->_head;
    for (uint32_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}


void *getIndex(List *list, uint32_t index) {
    nonNull(list);
    assert(index < list->size);

    ListElement *current = getListElementFromIndex(list, index);

    return current->payload;
}


void *popIndex(List *list, uint32_t index) {
    nonNull(list);
    assert(index < list->size);

    ListElement *current = getListElementFromIndex(list, index);

    void * payload = current->payload;
    unhookElement(list, current);

    return payload;
}


void *getCompare(List *list, void *payload, bool (*compareElemFunc)(void *payloadOne, void *payloadTwo)) {
    //todo: the following function takes over the check
    nonNull(list);
    nonNull(payload);
    nonNull(compareElemFunc);

    ListElement *current = getListElementFromCompare(list, payload, compareElemFunc);

    if (current == null){return null;}

    return current->payload;
}


void *popCompare(List *list, void *payload, bool (*compareElemFunc)(void *payloadOne, void *payloadTwo)) {
    //todo: the following function takes over the check
    nonNull(list);
    nonNull(payload);
    nonNull(compareElemFunc);

    ListElement *current = getListElementFromCompare(list, payload, compareElemFunc);

    if (current == null){return null;}

    void * returnPayload = current->payload;
    unhookElement(list, current);

    return returnPayload;
}


void *getFirst(List *list) {
    nonNull(list);
    return getIndex(list, 0);
}


void *popFirst(List *list) {
    nonNull(list);
    return popIndex(list, 0);
}


void clear(List *list, void (*deleteElemFunc)(void *payload)) {
    nonNull(list);
    nonNull(deleteElemFunc);

    for (uint32_t i = 0; i < list->size; ++i) {
        deleteElemFunc(list->popFirst(list));
    }
}


void delete(List *list, void (*deleteElemFunc)(void *payload)) {
    nonNull(list);

    if(list->size > 0){
        nonNull(deleteElemFunc);    //todo: can be removed later as "clear" catches this error.
        list->clear(list, deleteElemFunc);
    }
    free(list);
}


void extend(List *list, List *otherList) {
    nonNull(list);
    nonNull(otherList);

    for (uint32_t i = 0; i < otherList->size; ++i) {
        list->add(list, otherList->getIndex(otherList, i));
    }
}


List * new_List(){
    List *newList = calloc(1, sizeof(List));
    nonNull(newList);

    newList->add = add;

    newList->getFirst = getFirst;
    newList->getIndex = getIndex;
    newList->getCompare = getCompare;

    newList->popFirst = popFirst;
    newList->popIndex = popIndex;
    newList->popCompare = popCompare;

    newList->extend = extend;

    newList->remove = removeElem;
    newList->clear = clear;
    newList->delete = delete;

    return newList;
}
