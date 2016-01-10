#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "macros.h"

#define LCD_ADDR 0x50

int main (void)
{
    const uint8_t msg[] = "Hello";
    // --- Init ---
    initI2C();
    i2cStart();
    i2cSend(LCD_ADDR);
    i2cSend(0xFE);
    i2cSend(0x51);
    for (uint8_t i = 0; i < sizeof(msg); i++) {
        i2cStart();
        i2cSend(LCD_ADDR);
        i2cSend(msg[i]);
        _delay_ms(100);
    }
    _delay_ms(10000);
    i2cStart();
    i2cSend(LCD_ADDR);
    i2cSend(0xFE);
    i2cSend(0x51);
    i2cStop();
    while(1) {;};
}
