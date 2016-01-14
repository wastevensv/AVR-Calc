#include "mcp23017.h"
#include "i2c.h"

uint8_t mcp_read_register(uint8_t reg) {
    i2cStart();
    i2cSend(MCP_ADDR_W);
    i2cSend(reg);
    i2cStop();

    i2cStart();
    i2cSend(MCP_ADDR_R);
    uint8_t val = i2cReadNoAck();
    i2cStop();
    return val;
}

uint16_t mcp_read_register_pair(uint8_t reg) {
    i2cStart();
    i2cSend(MCP_ADDR_W);
    i2cSend(reg);
    i2cStop();

    i2cStart();
    i2cSend(MCP_ADDR_R);
    uint8_t a = i2cReadAck();
    uint8_t b = i2cReadNoAck();
    i2cStop();

    return (b << 8) | a;
}

void mcp_write_register(uint8_t reg , uint8_t val) {
    i2cStart();
    i2cSend(MCP_ADDR_W);
    i2cSend(reg);
    i2cSend(val);
    i2cStop();
}

void mcp_write_register_pair(uint8_t reg, uint16_t ab) {
    i2cStart();
    i2cSend(MCP_ADDR_W);
    i2cSend(reg);
    i2cSend(((ab >> 8) & 0xFF));
    i2cSend((ab & 0xFF));
    i2cStop();
}

uint16_t mcp_read_ab() {
    return mcp_read_register_pair(MCP_REG_GPIOA);
}

uint8_t mcp_read_a() {
    return mcp_read_register(MCP_REG_GPIOA);
}

uint8_t mcp_read_b() {
    return mcp_read_register(MCP_REG_GPIOB);
}

void mcp_write_ab(uint16_t ab) {
    mcp_write_register_pair(MCP_REG_GPIOA, ab);
}

void mcp_write_a(uint8_t a) {
    mcp_write_register(MCP_REG_GPIOA, a);
}

void mcp_write_b(uint8_t b) {
    mcp_write_register(MCP_REG_GPIOB, b);
}

