/*
 * driv_CAN.c
 *
 * Created: 01.10.2015 11:16:55
 *  Author: helgeanl
 */ 

//High level functions
#include "driv_CAN_node3.h"
#include "MCP2515.h"
#include "driv_mcp2515_node3.h"
#include "setup.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

static uint8_t g_rx_flag = 0;

void can_init(){
	mcp2515_init();
	
	//Enable interrupt when message is receieved, RX0IE=1, RX1IE = 1
	mcp2515_bit_modify(MCP_CANINTE,0x01,0xFF);
	mcp2515_bit_modify(MCP_CANINTE,0x02,0xFF);
	
}

void can_message_send(can_message_t* msg){
	while(!can_transmit_complete());								//	Wait until previous transfers is complete

	mcp2515_write(MCP_TXB0SIDH, (uint8_t)( msg->id >> 8) );			//  STANDARD IDENTIFIER HIGH
	mcp2515_write(MCP_TXB0SIDL, (uint8_t)( msg->id & 0x00FF ));		//  STANDARD IDENTIFIER LOW
	mcp2515_write(MCP_TXB0DLC, msg->data_length );					//	DATA LENGTH CODE
    
	for (uint8_t i = 0; i < msg->data_length; i++){
		mcp2515_write(MCP_TXB0D0 + i, msg->data[i]);
	}
	mcp2515_request_to_send();
}

uint8_t can_transmit_complete(){
	//Test if TXREQ, if currently pending transmission
	if(test_bit(mcp2515_read(MCP_TXB0CTRL),3)){
		return 0;
	}
	else{
		return 1;
	}
}


void can_message_receive(can_message_t* message){
	
	if(mcp2515_read(MCP_CANSTAT) & 0x0C){
		message->id = ((unsigned int) mcp2515_read(MCP_RXB0SIDH) << 8) | mcp2515_read(MCP_RXB0SIDL);
		message->data_length = mcp2515_read(MCP_RXB0DLC);
		for (uint8_t i = 0; i < message->data_length; i++){
			message->data[i] = mcp2515_read(MCP_RXB0D0 + i);
		}
		mcp2515_bit_modify(MCP_CANINTF, 0x01, 0);
	}
	
	else if(mcp2515_read(MCP_CANSTAT) & 0x0E){
		message->id = ((unsigned int) mcp2515_read(MCP_RXB1SIDH) << 8) | mcp2515_read(MCP_RXB1SIDL);
		message->data_length = mcp2515_read(MCP_RXB1DLC);
		for (uint8_t i = 0; i < message->data_length; i++){
			message->data[i] = mcp2515_read(MCP_RXB1D0 + i);
		}
		mcp2515_bit_modify(MCP_CANINTF, 0x02,0x00);
	}
	g_rx_flag = 0;
	
}

void can_int_vect() {
	//Clear interrupt flag
	mcp2515_bit_modify(MCP_CANINTF, 0x01, 0);
	mcp2515_bit_modify(MCP_CANINTF, 0x02,0x00);
	g_rx_flag = 1;
}

uint8_t can_get_rx_flag(){
	return g_rx_flag;
}
/*
//Interrupt service routine for CAN bus
ISR(INT2_vect) {
	_delay_ms(10);
	can_int_vect();
}*/