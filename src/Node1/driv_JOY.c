/*
 * driv_JOY.c
 *
 * Created: 10.09.2015 14:20:06
 *  Author: helgeanl
 */
#include <avr/io.h>
#include <stdio.h>
#include "driv_ADC.h"
#include "driv_JOY.h"
#include "setup.h"
#include "driv_CAN.h"

static uint8_t mid_x;
static uint8_t mid_y;

void joy_init(){
	//Setup the ADC
	adc_init();
	//Set button pins to input
	DDRB &= ~(1<<PINB2) & ~(1<<PINB3);
	DDRD &= ~(1<<PIND2);
	PORTD |= (1<<PIND2);
	//Calibrate joystick
	joy_calibrate();
}

void joy_calibrate(){
	mid_x = adc_read(1);
	mid_y = adc_read(2);
}

/*
LEFT button: 1 (PORTB2)
RIGHT button: 2 (PORTB3)
JOY button: 3 (PORTD2)
*/
uint8_t joy_button(uint8_t button){
	if(button < 1 || button > 3 ) {return 0;} //Make sure button not less than 1 or larger than 3
	if (button==3 && !test_bit(PIND, 2))
	{
		return 1;
	}
	else if (test_bit( PINB,  1+ button ) && button != 3)
	{
		return 1;
	}
	else{
		return 0;
	}
}


joy_position_t joy_get_position(){
	joy_position_t position;
	uint8_t x, y;
	//Read position y from channel 1
	y = adc_read(1);
	//Read position x from channel 2
	x = adc_read(2);
	position.x = (x)*(100+100)/(256)-100;
	position.y = (y)*(100+100)/(256)-100;
	return position;
	}
	
joy_direction_t joy_get_direction(){
	joy_position_t position;
	//Get actual position of joystick
	position = joy_get_position();
	
	if(position.x < -90) {
		return LEFT;
	} else if(position.x > 90) {
		return RIGHT;
	}
	
	if(position.y <= -92) {
		return DOWN;
	} else if(position.y > 80) {
		return UP;
	}
	return NEUTRAL;
}




