/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#include "listTest.h"
#include "list.h"
#include "event.h"

//todo: use ifPrint_Fatal

void addAndGetTest(){

    print_info("    Running Tests for add to list and get from list ...");

    uint32_t originalNumber = 2;

    List *testList = new_List();

    ifPrint_fatal(testList == null, "new_List() returned null");

    testList->add(testList, &originalNumber);

    ifPrint_fatal(testList->size != 1, "testList contains no Elements");

    uint32_t *returnNumber = testList->getFirst(testList);

    ifPrint_fatal(&originalNumber != returnNumber, "Pointer of original and return value is not the same");
    ifPrint_fatal(testList->size != 1, "testList contains no Elements after get a Element");

    testList->delete(testList, null);

    print_success("         Passed");
}

void addAndPopTest(){

    print_info("    Running Tests for add to list and pop from list ...");

    uint32_t originalNumber = 2;

    List *testList = new_List();

    testList->add(testList, &originalNumber);

    ifPrint_fatal(testList->size != 1, "testList contains no Elements");

    uint32_t *returnNumber = testList->popFirst(testList);

    ifPrint_fatal(&originalNumber != returnNumber, "Pointer of original and return value is not the same");
    ifPrint_fatal(testList->size != 0, "testList contains already elements");

    testList->delete(testList, null);

    print_success("         Passed");
}

void getIndexTest(){

    print_info("    Running Tests for get index from list ...");

    uint32_t originalNumberOne = 2;
    uint32_t originalNumberTwo = 3;

    List *testList = new_List();

    testList->add(testList, &originalNumberOne);
    testList->add(testList, &originalNumberTwo);

    ifPrint_fatal(testList->size != 2, "testList contains not enough Elements");

    uint32_t *returnNumberTwo = testList->getIndex(testList, 1);
    uint32_t *returnNumberOne = testList->getIndex(testList, 0);

    ifPrint_fatal(&originalNumberOne != returnNumberOne or &originalNumberTwo != returnNumberTwo, "Pointer of original and return value is not the same");
    ifPrint_fatal(testList->size != 2, "testList contains not enough elements after get");

    testList->delete(testList, null);

    print_success("         Passed");
}

void getCompareTest(){

    print_info("    Running Tests for get with compare from list ...");

    //todo:

    print_warning("         Test not implement ...");
}

void popIndexTest(){

    print_info("    Running Tests for pop index from list ...");

    uint32_t originalNumberOne = 2;
    uint32_t originalNumberTwo = 3;

    List *testList = new_List();

    testList->add(testList, &originalNumberOne);
    testList->add(testList, &originalNumberTwo);

    ifPrint_fatal(testList->size != 2, "testList contains not enough Elements");

    uint32_t *returnNumberOne = testList->popIndex(testList, 0);
    uint32_t *returnNumberTwo = testList->popIndex(testList, 0);

    ifPrint_fatal(&originalNumberOne != returnNumberOne or &originalNumberTwo != returnNumberTwo, "Pointer of original and return value is not the same");
    ifPrint_fatal(testList->size != 0, "testList contains to many elements after pop");

    testList->delete(testList, null);

    print_success("         Passed");
}

void popCompareTest(){

    print_info("    Running Tests for pop compare from list ...");

    //todo:

    print_warning("         Test not implement ...");
}

void extendTest(){

    print_info("    Running Tests for extend list ...");

    //todo:

    print_warning("         Test not implement ...");
}

void removeTest(){

    print_info("    Running Tests for remove from list ...");

    //todo:

    print_warning("         Test not implement ...");
}

void clearTest(){

    print_info("    Running Tests for clear list ...");

    //todo:

    print_warning("         Test not implement ...");
}

void deleteTest(){

    print_info("    Running Tests for delete list ...");

    //todo:

    print_warning("         Test not implement ...");
}

void listTest(){

    print_info("Running Tests for list.c");

    addAndGetTest();
    addAndPopTest();
    getIndexTest();
    getCompareTest();
    popIndexTest();
    popCompareTest();
    extendTest();
    removeTest();
    clearTest();
    deleteTest();
}
