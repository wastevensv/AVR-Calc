#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
    uint8_t   input_str[256];
    fgets(input_str,255,stdin);
    uint8_t*  nextc = input_str;
    while(*nextc != 0x00) {
        int64_t a, b = 0;
        switch (*nextc) {
            case '0' ... '9':
                push(strtol(nextc,&nextc,10));
                nextc--;
                break;
            case '+':
                a = pop();
                b = pop();
                push(a + b);
                break;
            case '-':
                a = pop();
                b = pop();
                push(b - a);
                break;
            case '*':
                a = pop();
                b = pop();
                push(b * a);
                break;
            case '/':
                a = pop();
                b = pop();
                push(b / a);
                break;
        }
        nextc++;
    }
    
    printf("%llu\n",pop());
    return 0;
}

