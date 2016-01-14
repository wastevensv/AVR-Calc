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

ISR(INT0_vect) {
    PORTB &= ~(BV(PB5));
    newkey=1;
}

void initInterrupt0(void) {
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
}

int main (void)
{
    uint8_t input[16] = {'\0'};
    uint8_t input_len = 0;
    uint8_t i=0;
    uint8_t key='F';
    uint8_t keycode=0xFFFF;

    DDRB |= BV(PB5);
    PORTB |= BV(PB5);
    initI2C();

    mcp_write_register_pair(MCP_REG_IODIRA, 0xFFFF);
    mcp_write_register_pair(MCP_REG_GPPUA, 0xFFFF);
    mcp_write_register_pair(MCP_REG_IOCON, 0b01000000);
    mcp_write_register_pair(MCP_REG_GPINTENA, 0xFFFF);
    //mcp_write_register_pair(MCP_REG_DEFVALA, 0xFFFF);
    //mcp_write_register_pair(MCP_REG_INTCONA, 0xFFFF);

    lcd_clear();

    lcd_print("Hi!");

    initInterrupt0();
    
    sei();
    while (1) {
        _delay_ms(100);
        if(newkey == 1) {
            cli();
            keycode = mcp_read_register_pair(MCP_REG_INTFA);
            key = 'U';
            for(i = 0; i < KEY_COUNT; i++) {
                if(keycode == keycodes[i]) key = keyvals[i];
            }

            lcd_clear();
            if(key != '=') {
                input[input_len++] = key;
                lcd_print(input);
            }
            keycode = 0xFFFF;
            newkey = 0;
            PORTB |= BV(PB5);
            sei();
        }
    }
}
