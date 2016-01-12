#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    uint8_t   input_str[] = "2 22+ 66 -";
    uint8_t*  nextc = input_str;
    
    int64_t  stack[16];
    int64_t* stack_top = stack;
    
    while(*nextc != 0x00) {
        switch (*nextc) {
            case '0' ... '9':
                *(++stack_top) = strtol(nextc,&nextc,10);
                nextc--;
                break;
            case '+':
                *(stack_top) = *(stack_top) + *(--stack_top);
                break;
            case '-':
                *(stack_top) = *(stack_top) - *(--stack_top);
                break;
            case '*':
                *(stack_top) = *(stack_top) * *(--stack_top);
                break;
            case '/':
                *(stack_top) = *(stack_top) / *(--stack_top);
                break;
        }
        nextc++;
    }
    
    printf("%lli\n",*stack_top);
    return 0;
}

