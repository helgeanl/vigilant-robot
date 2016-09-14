/*
 * main.c
 *
 * Created: 27.08.2015 12:50:37
 * Author: Helge-AndrŽ Langåker, Johan Vårlid
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "setup.h"
#include "Xmem.h"
#include "driv_mcp2515.h"
#include "MCP2515.h"
#include "driv_UART.h"
#include "driv_JOY.h"
#include "driv_CAN.h"
#include "fsm.h"


int main(void)
{
	
	// Initialize registers...
	DDRA = 0x00;
	DDRC = (1<< DDC0)|(1<< DDC1)|(1<< DDC2)|(1<< DDC3);
	DDRE = (1<< DDE1);
	DDRD = (1<< DDD6)|(1<<DDD7);
	
	// Set relay signal pin to output
	DDRD |= (1<<PD4);
	clear_bit(DDRD,PD4);
	
    	// Initialization of drivers
	usart_init(MYUBRR);
	xmem_init();
	joy_init();
	oled_init();
	can_init();
	fsm_init();
	sei(); 		// Enable interrupts
	
	// Button and joystick states
	joy_direction_t current_state_joy	= NEUTRAL;
	joy_direction_t previous_state_joy	= NEUTRAL;
	uint8_t current_state_left_but		= 0;
	uint8_t previous_state_left_but     	= 0;
	uint8_t current_state_right_but     	= 0;
	uint8_t previous_state_right_but	= 0;
	uint8_t previous_state_joy_but		= 0;
	uint8_t current_state_joy_but		= 0;
	
	// Joystick
	joy_position_t 	joy_pos;
    
	 // CAN
	 can_message_t       joy_pos_msg;
	 can_message_t       slider_pos_msg;
	 can_message_t       received_msg;
    
	while(1)
	{
		// Receive message from CAN
		if(mcp2515_read(MCP_CANSTAT) & 0x0C || mcp2515_read(MCP_CANSTAT) & 0x0E)
		{ 
			can_message_receive(&received_msg);
			fsm_can(&received_msg);
		}
		//  Event handling of buttons
		current_state_left_but = joy_button(LEFT_BUTTON); // Left button
		if (current_state_left_but != previous_state_left_but)
		{	
			previous_state_left_but = current_state_left_but;
			if(joy_button(LEFT_BUTTON))
			{
				fsm_left_button();
			}
		}
		current_state_right_but = joy_button(RIGHT_BUTTON); // Right button
		if (current_state_right_but != previous_state_right_but)
		{	
			previous_state_right_but = current_state_right_but;
			if(joy_button(RIGHT_BUTTON))
			{
				fsm_right_button();
			}
		}
		
		current_state_joy_but = joy_button(JOY_BUTTON); // Joy button
		if (current_state_joy_but != previous_state_joy_but)
		{
			previous_state_joy_but = current_state_joy_but;
			if(joy_button(JOY_BUTTON))
			{
				fsm_joy_button();
			}
		}
		
		//  Event handling of joystick
		current_state_joy = joy_get_direction();
		if(current_state_joy !=previous_state_joy)
		{
			previous_state_joy=current_state_joy;
			if( joy_get_direction() == DOWN)
			{
				fsm_joy_down();
			}
			else if(joy_get_direction() == UP)
			{
				fsm_joy_up();
			}
			if(joy_get_direction() == RIGHT)
			{
				fsm_joy_right();
				
			}
			if(joy_get_direction() == LEFT)
			{
				fsm_joy_left();
			}
		}
		fsm_refresh_screen();
		_delay_ms(10);
	}
}
