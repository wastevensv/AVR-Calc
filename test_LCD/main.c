#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "macros.h"
#include "lcd.h"

int main (void)
{
    const uint8_t fst[] = "Hello";
    const uint8_t snd[] = "World";

    initI2C();
    lcd_clear();
    lcd_print(fst);
    lcd_move(1,0);
    lcd_print(snd);
    while(1) {;};
}
