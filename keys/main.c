#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include "macros.h"
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
      '3', '6', '9', '=',
      '2', '5', '8', '0',
      '1', '4', '7', ' '
    };

const uint8_t hexkey[16] = "0123456789ABCDEF";

ISR(INT0_vect) {
    PORTB &= ~(BV(PB5));
    newkey=1;
}

void initInterrupt0(void) {
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01);
}

int main (void)
{
    uint8_t input[16] = {'\0'};
    uint8_t input_len = 0;
    uint8_t i=0;
    uint8_t key='F';
    uint16_t keycode=0xFFFF;

    DDRB |= BV(PB5);
    PORTB |= BV(PB5);
    initI2C();

    mcp_write_register(MCP_REG_IODIRA, 0xFF);
    mcp_write_register(MCP_REG_IODIRB, 0xFF);
    mcp_write_register(MCP_REG_GPPUA, 0xFF);
    mcp_write_register(MCP_REG_GPPUB, 0xFF);
    mcp_write_register(MCP_REG_IPOLA, 0x00);
    mcp_write_register(MCP_REG_IPOLB, 0x00);
    //mcp_write_register_pair(MCP_REG_IOCON, 0b01000000);
    //mcp_write_register_pair(MCP_REG_GPINTENA, 0xFFFF);
    //mcp_write_register_pair(MCP_REG_DEFVALA, 0xFFFF);
    //mcp_write_register_pair(MCP_REG_INTCONA, 0xFFFF);

    lcd_clear();

    lcd_print("Hi!");

    //initInterrupt0();
    
    //sei();
    while (1) {
        //keycode = mcp_read_register_pair(MCP_REG_INTFA);
        keycode = mcp_read_a();
        keycode |= (mcp_read_b() << 8);
        lcd_clear();
        input[input_len++] = hexkey[((keycode & 0xF000) >> 12)];
        input[input_len++] = hexkey[((keycode & 0x0F00) >> 8)];
        input[input_len++] = hexkey[((keycode & 0x00F0) >> 4)];
        input[input_len++] = hexkey[ (keycode & 0x000F)];
        lcd_print(input);
        input_len = 0;
        keycode = 0x0000;
        newkey = 0;
        _delay_ms(250);
    }
}
