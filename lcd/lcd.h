#ifndef _LCD_H_
#define _LCD_H_

#include <stdint.h>

#define LCD_ADDR 0x50

void lcd_clear();

void lcd_move(uint8_t row, uint8_t col);

void lcd_print(const uint8_t* str);

#endif

