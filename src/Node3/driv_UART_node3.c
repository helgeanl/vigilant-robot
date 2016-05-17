/*
 * driv_UART.c
 *
 * Created: 27.08.2015 14:57:55
 *  Author: Administrator
 */
#include <avr/io.h>


unsigned char usart_receive(void)
{
    /* Wait for data to be received */
    while( !(UCSR1A & (1<<RXC1)) );
    /* Get and return received data from buffer */
    return UDR1;
}

void usart_transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while( !( UCSR1A & (1<<UDRE1)) );
    /* Put data into buffer, sends the data */
    UDR1 = data;
}


void usart_init(uint8_t ubrr)
{

    /* Set baud rate*/
    UBRR1L = ubrr;
    /* Enable receiver and transmitter*/
    UCSR1B = (1<<RXEN1)|(1<<TXEN1);
    /* Enable printf */
    fdevopen(usart_transmit, usart_receive);
}


