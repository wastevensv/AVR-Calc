#ifndef _MCP23017_H_
#define _MCP23017_H_

#include <stdint.h>

#define MCP_ADDR_W 0x40
#define MCP_ADDR_R 0x41

#define MCP_REG_IODIRA      0x00
#define MCP_REG_IODIRB      0x01
#define MCP_REG_IPOLA       0x02
#define MCP_REG_IPOLB       0x03
#define MCP_REG_GPINTENA    0x04
#define MCP_REG_GPINTENB    0x05
#define MCP_REG_DEFVALA     0x06
#define MCP_REG_DEFVALB     0x07
#define MCP_REG_INTCONA     0x08
#define MCP_REG_INTCONB     0x09
#define MCP_REG_IOCON       0x0A

#define MCP_REG_GPPUA       0x0C
#define MCP_REG_GPPUB       0x0D
#define MCP_REG_INTFA       0x0E
#define MCP_REG_INTFB       0x0F
#define MCP_REG_INTCAPA     0x10
#define MCP_REG_INTCAPB     0x11
#define MCP_REG_GPIOA       0x12
#define MCP_REG_GPIOB       0x13
#define MCP_REG_OLATA       0x14
#define MCP_REG_OLATB       0x15

uint8_t  mcp_read_register(uint8_t reg);
uint16_t mcp_read_register_pair(uint8_t reg);

void     mcp_write_register(uint8_t reg, uint8_t val);
void     mcp_write_register_pair(uint8_t reg, uint16_t val);

uint16_t mcp_read_ab();

uint8_t  mcp_read_a();
uint8_t  mcp_read_b();

void     mcp_write_ab(uint16_t ab);

void     mcp_write_a(uint8_t a);
void     mcp_write_b(uint8_t b);
#endif
