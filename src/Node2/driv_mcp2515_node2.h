/*
 * driv_mcp2515.h
 *
 * Created: 01.10.2015 11:54:37
 *  Author: helgeanl
 */ 


#ifndef DRIV_MCP2515_H_INCLUDED
#define DRIV_MCP2515_H_INCLUDED

#define DDR_SPI     DDRB
#define CS_MCP2515  53
#define DD_MOSI     51
#define DD_MISO     50
#define DD_SCK      52
#define DD_INT      2 // PE4 INT4

uint8_t mcp2515_read(uint8_t address);
void    mcp2515_write(uint8_t address, char data);
void    mcp2515_request_to_send();
void    mcp2515_bit_modify(uint8_t address, char mask, char data);
void    mcp2515_reset();
uint8_t mcp2515_read_status();
uint8_t mcp2515_init();
void    mcp2515_test();


#endif /* DRIV_MCP2515_H_ */
