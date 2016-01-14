#include "stack.h"

DTYPE items[MAXSTACK+1];
uint8_t top=-1;

uint8_t push(DTYPE e) {
    if(top != MAXSTACK) {
        items[++top] = e;
        return 0;
    } else {
        return -1;
    }
}
DTYPE pop() {
    if(top >= 0) {
        return items[top--];
    } else {
        return -1;
    }
}
