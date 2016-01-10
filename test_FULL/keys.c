#include "keys.h"

uint8_t GetKeyPressed() {
    const uint8_t keymap[] = {'6', '7', '8', '9', '0', 
                              '1', '2', '3', '4', '5' ,
                              '+', '-', '*', '/', '='};

    KP_COL_PORT |=  (KP_COL_MASK);  // Enable column pullups.
    KP_ROW_DDR  |=  (KP_ROW_MASK);
    KP_ROW_PORT &= ~(KP_ROW_MASK); // Clear all row pins to low.
    for(uint8_t row = 0; row < 3; row++) { // Scan rows.
        KP_ROW_PORT |= BV(row+2); // Set row select high.
        for(uint8_t col = 0; col < 5; col++) { // Scan columns.
            if(bit_is_clear(KP_COL_PIN, col)) { // Check each column.
                KP_ROW_PORT &= ~BV(row+2);
                return keymap[(row*5)+col]; // Return value from keymap
            }
        }
        KP_ROW_PORT &= ~BV(row+2); // Set row select low.
    }
    return 0xFF; // Send 0xFF if no key pressed.
}
