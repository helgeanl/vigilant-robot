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

/************************************************************************/
/*                      Public functions                                */
/************************************************************************/

uint8_t adc_read(char ch){
	volatile uint8_t *adc = (uint8_t *) 0x1400;
	if(ch > 4) {return 0;} //Make sure ch not above 4
	adc[0]=0x03+ch;
	//Wait for the data to be read 
	while(test_bit(PINE, PINE0));
	return *adc;	
}

void adc_init(void) {
	//Enable the external memory interface/4 bits address
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
	//Set the interrupt pin to input
	DDRE &= ~(1<<PINE0);
}