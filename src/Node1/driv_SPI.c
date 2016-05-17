/*
 * driv_SPI.c
 *
 * Created: 01.10.2015 11:11:36
 *  Author: helgeanl
 */ 
#include <avr/io.h>
#include "driv_SPI.h"


void spi_send(uint8_t data){
	/*Start transmission*/
	SPDR = data;
	/*Wait for transmission complete*/
	while (!(SPSR & (1<<SPIF)));
}
uint8_t spi_read(){
	spi_send(0x00); // Send dummy byte
	/*Wait for reception complete*/
	while (!(SPSR & (1<<SPIF)));
	// Return data register
	return SPDR;
}
void spi_init(){
	/*Set MOSI and SCK outout, all others input*/
	DDR_SPI |= (1<<DD_MOSI) | (1<<DD_SCK) | (1<<CS_MCP2515);
	/* Enable SPI, Master, set clock rate fck/16*/
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0); 
}

