/*
 * driv_mcp2515.c
 * rev: 1
 * Created: 01.10.2015 11:50:39
 *  Author: helgeanl
 */ 


#include "SPI.h"
#include "MCP2515.h"
#include "driv_mcp2515_node2.h"
#include "setup.h"
#include <stdio.h>
#include <Arduino.h>
//#include <avr/pgmspace.h>

// Read data from register beginning at selected address.
uint8_t mcp2515_read(uint8_t address){
    uint8_t result;
    digitalWrite(CS_MCP2515,LOW);   // Select Can-Controller
    SPI.transfer(MCP_READ);         // Send read command
    SPI.transfer(address);          // Send address 
    result = SPI.transfer(0x00);    // Read result
    digitalWrite(CS_MCP2515,HIGH);    // Deselect CAN-controller
    return result;
}

// Write data to register beginning at selected address.
void mcp2515_write(uint8_t address, char data ){
    digitalWrite(CS_MCP2515,LOW);   // Select Can-Controller
    SPI.transfer(MCP_WRITE);        // Send write command
    SPI.transfer(address);          // Send address 
    SPI.transfer(data);             // Send data
    digitalWrite(CS_MCP2515,HIGH);  // Deselect CAN-controller
}

// Instructs controller to begin message transmission sequence for all the the transmit buffers.
void mcp2515_request_to_send(){
    digitalWrite(CS_MCP2515,LOW);   // Select Can-Controller
    SPI.transfer(MCP_RTS_TX0);        // Send RTS command for all buffers
    digitalWrite(CS_MCP2515,HIGH);      // Deselect Can-Controller
}

// Allows the user to set or clear individual bits in a particular register.
void mcp2515_bit_modify(uint8_t address, char mask, char data){
    digitalWrite(CS_MCP2515,LOW);   // Select Can-Controller
    SPI.transfer(MCP_BITMOD);       // Send BIT MODIFY command
    SPI.transfer(address);          // Send address 
    SPI.transfer(mask);           // Send mask byte
    SPI.transfer(data);           // Send data byte  
    digitalWrite(CS_MCP2515,HIGH);      // Deselect Can-Controller
}

//  Resets internal registers to default state and set Configuration mode. 
void mcp2515_reset(){
    digitalWrite(CS_MCP2515,LOW);   // Select Can-Controller
    SPI.transfer(MCP_RESET);        // Send Reset command
    digitalWrite(CS_MCP2515,HIGH);      // Deselect Can-Controller
}

// Quick polling command that reads several status bits for transmit and receive functions.
uint8_t mcp2515_read_status(){ //OVERSATT
    uint8_t status;
    digitalWrite(CS_MCP2515, LOW);  // Select Can-Controller
    SPI.transfer(MCP_READ_STATUS);  // Send Read Status command
    status = SPI.transfer(0x00);
    digitalWrite(CS_MCP2515,HIGH);  // Deselect Can-Controller
    return status;
}

uint8_t mcp2515_init(){
    SPI.begin();                        // Initialize SPI
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    SPI.endTransaction();
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    mcp2515_reset();                    // Send reset-command, should work
    delay(50);
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





