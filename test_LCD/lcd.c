#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

void lcd_clear() {
    i2cStart();
    i2cSend(LCD_ADDR);
    i2cSend(0xFE);
    i2cSend(0x51);
    i2cStop();
}

void lcd_move(uint8_t row, uint8_t col) {
    row = row * 0x40; // row 0 = 0x0?,  row 1 = 0x4?
    row = row | col; // col is low nibble.
    i2cStart();
    i2cSend(LCD_ADDR);
    i2cSend(0xFE);
    i2cSend(0x45);
    i2cSend(row);
    i2cStop();
}

void lcd_print(const uint8_t* msg) {
    for(int8_t i=0; msg[i] != '\0'; i++) {
        i2cStart();
        i2cSend(LCD_ADDR);
        i2cSend(msg[i]);
        i2cStop();
    }
}
