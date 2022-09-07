/*
 * Projekt URL: https://github.com/Michel-Schnitker/SweepMyCMine
 * License:     MIT License
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>


#define null NULL
#define ever (;;)

#define not !
#define and &&
#define or ||

#define SUCCESS 0
#define ERROR (-1)

#define nonNull(it) assert((it) != NULL)

#define UNREACHABLE assert(false)


#endif  // TYPES_H_
