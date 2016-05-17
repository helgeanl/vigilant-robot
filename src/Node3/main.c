/*
 * main.c
 *
 * Created: 08.11.2015 00:24:33
 *  Author: johanvaa
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "touch.h"
#include "melody.h"
#include "setup.h"
#include "driv_CAN_node3.h"
#include "MCP2515.h"
#include "driv_mcp2515_node3.h"
#include "driv_UART_node3.h"
#include <avr/interrupt.h>
#include <stdio.h>




#define STATE_MENU      1
#define	STATE_GAME      2
#define	STATE_CALIBRATE 3
#define	STATE_DEBUG     4
#define	STATE_PID       5
#define	STATE_GAME_OVER 6
static uint8_t ms_tick2;

#define JOYSTICK    1
#define PLAYSTATION 2

int main(void)
{
	touch_init(30, 30, 30, 30);
	DDRB &= ~(1<<PB7);	// Turn off buzzer for now by setting PORTB.0 = input
	DDRD &= ~(1<<PD2);	// Set PD2/INT2 as input

	sei();
	usart_init(MYUBRR);
	can_init();
	melody_init();
    
	//set PB1 to output
	DDRB |= (1<<MELODY_PIN)|(1<<PB5)|(1<<PB4);	// PB5 = Left button
	DDRD |= (1<<PD0)|(1<<PD1);					// PD0 = Right button
	
    uint8_t ls, rs, lb, rb;
    uint8_t game_melody = 1;

	uint8_t game_controller = 1;
	
    uint8_t state = STATE_MENU;
	can_message_t can_receive_msg;
	can_message_t can_send_msg;
	can_send_msg.id = SLIDER_ID;
	can_send_msg.data_length = 2;
	ms_tick2=0;
	melody_play(8);

	while(1)
	{
		
		touch_measure(&ls, &rs, &lb, &rb);
        
        // Left and Right button, always check if pressed
        if (lb)
            set_bit(PORTB,PB5);
        else
            clear_bit(PORTB,PB5);
        if (rb)
            set_bit(PORTD,PD0);
        else
            clear_bit(PORTD,PD0);
        
        // State machine
        switch (state) {
            case STATE_MENU:
                break;
            case STATE_GAME:
                if(melody_get_play_tune() == 0){
                    melody_play(game_melody);
                }
				if (game_controller == JOYSTICK)
				{
					if (ms_tick2>100)
					{
						can_send_msg.data_length = 1;
						can_send_msg.data[0] = rs;
						can_message_send(&can_send_msg);
						ms_tick2=0;
					}
				}
                break;
            case STATE_GAME_OVER:
                break;
            case STATE_CALIBRATE:
				if (ms_tick2>100)
				{
					can_send_msg.data_length = 2;
					can_send_msg.data[0] = ls;
					can_send_msg.data[1] = rs;
					can_message_send(&can_send_msg);
				}
                break;
            case STATE_DEBUG:
                break;
            default:
                break;
        }
		
		if(mcp2515_read(MCP_CANSTAT) & 0x0C || mcp2515_read(MCP_CANSTAT) & 0x0E){
			printf("CAN\n");
			can_message_receive(&can_receive_msg);
			_delay_ms(15);
			switch (can_receive_msg.id) {
				case GAME_ID:
					state = STATE_GAME;
                    break;
				case SLIDER_ID:
					printf("Slider\n");
                    break;
				case CONTROLLER_ID:
					game_controller = can_receive_msg.data[0];
                    break;
				case SCORE_ID:
					break;	
				case STATE_ID:
                    state = can_receive_msg.data[0];
					printf("State: %d\n", state);
					if(state == STATE_GAME_OVER){
						melody_play(8);
					}
                    break;
				case SOUND_ID:
					if(can_receive_msg.data[0] > 0 && can_receive_msg.data[0] < 6){
                        game_melody = can_receive_msg.data[0];
                        melody_play(game_melody);
                    }
                    else if(can_receive_msg.data[0] > 0){
                        melody_play(can_receive_msg.data[0]);
                    }
                    else{
                        melody_stop();
                    }
                    break;
				default:
                    break;
			}
		}
	}
}

ISR(TIMER0_COMPB_vect){//Reduce CAN buss load
	ms_tick2++;
}