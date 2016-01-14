#ifndef _STACK_H_
#define _STACK_H_

#include <stdint.h>
#include <stdlib.h>

#define MAXSTACK  16
#define DTYPE     uint64_t


uint8_t push(DTYPE e);
DTYPE pop();
#endif
