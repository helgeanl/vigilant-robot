/*
 * driv_UART.h
 *
 * Created: 27.08.2015 14:58:24
 *  Author: Administrator
 */ 


#ifndef DRIV_UART_H_
#define DRIV_UART_H_

#include <stdio.h> 

void usart_init(unsigned int ubrr);
void usart_transmit( unsigned char data);
unsigned char usart_receive( void);


#endif /* DRIV_UART_H_ */