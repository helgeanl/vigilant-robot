/*
 * driv_UART.c
 *
 * Created: 27.08.2015 14:57:55
 *  Author: Helge-André Langåker
 */ 
#include <avr/io.h>


unsigned char usart_receive(void)
{
	/* Wait for data to be received */
	while( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

void usart_transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
    while( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
}


void usart_init(uint8_t ubrr)
{
	/* Set baud rate*/
    UBRR0L = ubrr;
	/* Enable receiver and transmitter*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Enable printf */
	fdevopen(usart_transmit, usart_receive);
}

