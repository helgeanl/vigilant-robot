/*
 * driv_mcp2515.c
 * rev: 1
 * Created: 01.10.2015 11:50:39
 *  Author: helgeanl
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#include "MCP2515.h"
#include "driv_mcp2515.h"
#include "driv_SPI.h"
#include "setup.h"


// Read data from register beginning at selected address.
uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	clear_bit(PORTB, CS_MCP2515);		// Select Can-Controller
	spi_send(MCP_READ);					// Send read command
	spi_send(address);					// Send address
	result = spi_read();				// Read result
	set_bit(PORTB, CS_MCP2515);			// Deselect CAN-controller
	return result;
}

// Write data to register beginning at selected address.
void mcp2515_write(uint8_t address, char data ){
	clear_bit(PORTB, CS_MCP2515);		// Select Can-Controller
	spi_send(MCP_WRITE);				// Send write command
	spi_send(address);					// Send address
	spi_send(data);						// Send data
	set_bit(PORTB, CS_MCP2515);			// Deselect CAN-controller
}

// Instructs controller to begin message transmission sequence for all the the transmit buffers.
void mcp2515_request_to_send(){
	clear_bit(PORTB, CS_MCP2515);		// Select Can-Controller
	spi_send(0b10000001);				// Send RTS command for all buffers
	set_bit(PORTB, CS_MCP2515);			// Deselect Can-Controller
}

// Allows the user to set or clear individual bits in a particular register.
void mcp2515_bit_modify(uint8_t address, char mask, char data){
	clear_bit(PORTB, CS_MCP2515);		// Select Can-Controller
	spi_send(MCP_BITMOD);				// Send BIT MODIFY command
	spi_send(address);					// Send address
	spi_send(mask);						// Send mask byte
	spi_send(data);						// Send data byte
	set_bit(PORTB, CS_MCP2515);			// Deselect Can-Controller
}

//  Resets internal registers to default state and set Configuration mode. 
void mcp2515_reset(){
	clear_bit(PORTB, CS_MCP2515);		// Select Can-Controller
	spi_send(MCP_RESET);				// Send Reset command
	set_bit(PORTB, CS_MCP2515);			// Deselect Can-Controller
}

// Quick polling command that reads several status bits for transmit and receive functions.
uint8_t mcp2515_read_status(){
	uint8_t status;
	clear_bit(PORTB, CS_MCP2515);		// Select Can-Controller
	spi_send(MCP_READ_STATUS);			// Send Read Status command
	status = SPI_read();				
	set_bit(PORTB, CS_MCP2515);			// Deselect Can-Controller
	return status;
}

uint8_t mcp2515_init(){
	spi_init();							// Initialize SPI
	mcp2515_reset();					// Send reset-command
	_delay_ms(50);
	//Self-test
	if((mcp2515_read(MCP_CANSTAT) & MODE_MASK)  != MODE_CONFIG) {
		return 1;
	}
	// Filter intitialization
	mcp2515_write(MCP_RXB0CTRL,0x60);
	mcp2515_write(MCP_RXB1CTRL,0x60);
	
	mcp2515_bit_modify(MCP_CANCTRL,MODE_MASK,MODE_NORMAL);
	if((mcp2515_read(MCP_CANSTAT) & MODE_MASK)  != MODE_NORMAL) {
		return 1;
	}
	return 0;
}

