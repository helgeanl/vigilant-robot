/*
 * xmem.c
 *
 * Created: 03.09.2015 12:30:41
 *  Author: helgeanl
 */ 
#include <avr/io.h>
#include <stdlib.h>

void xmem_init(){
	MCUCR |= (1<<SRE); 	// Enable external memory
	SFIOR |= (1<<XMM2); 	// Mask out addr. A12-A15 (are used as JTAG pins instead)
	MCUCR |= (1<<SRW10); 	// Add wait cycle on read/write
	EMCUCR |= (1<<SRW11); 	// Add wait cycle on read/write
}
