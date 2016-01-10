#include <avr/io.h>
#include "keys.h"


int main() {
    DDRB |= BV(PB5);
    const uint8_t key = 0xFF; 
    while(1) {
        if(GetKeyPressed() != key) {
            PORTB |= BV(PB5);
        } else {
            PORTB &= ~BV(PB5);
        }
    }
}
