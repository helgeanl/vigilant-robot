/*
 * driv_ADC.c
 *
 * Created: 10.09.2015 13:30:03
 *  Author: helgeanl
 */ 
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "setup.h"
#include <avr/interrupt.h>

static uint8_t adc_int_flag;

/************************************************************************/
/*                      Public functions                                */
/************************************************************************/

uint8_t adc_read(char ch){
	volatile uint8_t *adc = (uint8_t *) 0x1400;
	if(ch > 4) {return 0;} //Make sure ch not above 4
	adc[0]=0x03+ch;
	//Wait for the data to be read 
	while(!adc_int_flag);
	return *adc;	
}

void adc_init(void) {
	//Enable the external memory interface/4 bits address
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
	//Set the interrupt pin to input
	GICR |= (1<<INT0); 		// External Interrupt Request 0 Enable
	MCUCR |= (1<<ISC00)|(1<<ISC01); // The rising edge of INT0 generates an interrupt request.
	adc_int_flag = 0;
}


ISR(INT0_vect){
	adc_int_flag = 1;
}
