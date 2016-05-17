/*
 * xmem.c
 *
 * Created: 03.09.2015 12:30:41
 *  Author: helgeanl
 */ 
#include <avr/io.h>
#include <stdlib.h>

void xmem_init(){
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	MCUCR |= (1<<SRW10);
	EMCUCR |= (1<<SRW11);
}