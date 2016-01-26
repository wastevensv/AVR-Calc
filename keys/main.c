#include <util/delay.h>
#include "i2c.h"
#include "lcd.h"
#include "mcp23017.h"

#define KEY_COUNT 16

volatile uint8_t newkey = 0;

const uint16_t keycodes[KEY_COUNT] = 
    { 0x8000, 0x4000, 0x2000, 0x1000,
      0x0800, 0x0400, 0x0200, 0x0100,
      0x0080, 0x0040, 0x0020, 0x0010,
      0x0008, 0x0004, 0x0002, 0x0001
    };

const uint8_t keyvals[KEY_COUNT] =
    { '/', '*', '-', '+',
      '=', ' ', '9', '8',
      '7', '6', '5', '4',
      '3', '2', '1', '0'
    };

const uint8_t hexkey[16] = "0123456789ABCDEF";

int main (void)
{
    uint8_t input[16] = {'\0'};
    uint8_t input_len = 0;
    uint8_t i=0;
    uint8_t key='x';
    uint16_t keycode=0xFFFF;

    initI2C();

    mcp_write_register(MCP_REG_IOCON, 0x60);
    mcp_write_register_pair(MCP_REG_IPOLA, 0xFFFF);

    lcd_clear();

    lcd_print("Hi!");

    while (1) {
        keycode = 0x0000;
        keycode = ~mcp_read_ab();
        
        _delay_ms(250);

        input_len = 0;
        input[input_len++] = hexkey[ (keycode & 0x000F)];
        input[input_len++] = hexkey[((keycode & 0x00F0) >> 4)];
        input[input_len++] = hexkey[((keycode & 0x0F00) >> 8)];
        input[input_len++] = hexkey[((keycode & 0xF000) >> 12)];

        key = 'x';
        for(i = 0; i < KEY_COUNT; i++) {
            if(keycode == keycodes[i]) key = keyvals[i];
        }

        if(key != 'x') {
            input[input_len++] = ' ';
            input[input_len++] = key;
        }
        input[input_len++] = '\0';

        lcd_clear();
        lcd_print(input);
    }
}
