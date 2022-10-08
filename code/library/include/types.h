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

#define stringFromBool(b) ((b) ? "True" : "False")
#define isAlphabetKey(c) ((c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z'))
#define isNumberKey(c) (c >= '0' and c <= '9')

#endif  // TYPES_H_
