#ifndef LIST_H_
#define LIST_H_

#include <types.h>

typedef struct ListElement {
    struct ListElement *next;
    struct ListElement *prev;
    void *payload;
} ListElement;

/**
 * Notes for the documentary:
 *      delete      List must be empty to delete. If the list is not empty when deleting, the delete function is executed for each payload.
 *      remove      If the compare function is zero the pointer is compared, if not then the function decides if these payloads are equal.
 *      remove      if the delete function is non-zero, the payload is executed on the delete function, if not, the payload is not deleted.
 *
 *
 *
 */

/**
 *  add         :    \\todo:
 *  getFirst    :    \\todo:
 *  getIndex    :    \\todo:
 *  getCompare  :    \\todo:
 *  popFirst    :    \\todo:
 *  popIndex    :    \\todo:
 *  popCompare  :    \\todo:
 *  extend      :    \\todo:
 *  remove      :    \\todo:
 *  clear       :    \\todo:
 *  delete      :    \\todo:
 */


typedef struct List {
    ListElement *_head;
    ListElement *_tail;
    uint32_t size;

    void (*add)(struct List *list, void *object);

    void *(*getFirst)(struct List *list);
    void *(*getIndex)(struct List *list, uint32_t index);
    void *(*getCompare)(struct List *list, void *payload, int (*compareElemFunc)(void *payloadOne, void *payloadTwo));

    void *(*popFirst)(struct List *list);
    void *(*popIndex)(struct List *list, uint32_t index);
    void *(*popCompare)(struct List *list, void *payload, int (*compareElemFunc)(void *payloadOne, void *payloadTwo));

    void (*extend)(struct List *list, struct List *otherList);

    void (*remove)(struct List *list, void *payload, int (*compareElemFunc)(void *payloadOne, void *payloadTwo), void (*deleteElemFunc)(void *payload));
    void (*clear)(struct List *list, void (*deleteElemFunc)(void *payload));
    void (*delete)(struct List *list, void (*deleteElemFunc)(void *payload));

} List;

List * createList();

#endif  // LIST_H_
