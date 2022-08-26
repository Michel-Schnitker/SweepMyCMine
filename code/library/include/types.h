#ifndef TYPES_H_
#define TYPES_H_

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>


#define null NULL

#define not !
#define and &&
#define or ||

#define SUCCESS 0
#define ERROR (-1)

#define nonNull(it) assert((it) != NULL)

#define UNREACHABLE assert(false)


#endif  // TYPES_H_
