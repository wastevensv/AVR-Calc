#ifndef _KEYS_H_
#define _KEYS_H_

#include <avr/io.h>
#include "macros.h"

#define KP_ROW_DDR      DDRD
#define KP_ROW_PORT     PORTD
#define KP_ROW_MASK     0b00011100

#define KP_COL_PORT     PORTB
#define KP_COL_MASK     0b00011111
#define KP_COL_PIN      PINB


const uint8_t keymap[] = {'6', '7', '8', '9', '0', 
                        '1', '2', '3', '4', '5' ,
                        '+', '-', '*', '/', '='};

uint8_t GetKeyPressed();

#endif
