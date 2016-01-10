#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "keys.h"
#include "macros.h"

#define LCD_ADDR 0x50

int main (void)
{
    // --- Init ---
    initI2C();
    i2cStart();
    i2cSend(LCD_ADDR);
    i2cSend(0xFE);
    i2cSend(0x51);
    uint8_t key = GetKeyPressed();
    while (key != '=') {
        key = GetKeyPressed();
        if(key != 0xFF) {
            i2cStart();
            i2cSend(LCD_ADDR);
            i2cSend(key);
            _delay_ms(200);
        }
    }
    i2cStop();
    while(1) {;};
}
