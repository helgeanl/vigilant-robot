/*
 * setup.h
 *
 * Created: 08.11.2015 00:22:50
 *  Author: johanvaa
 */ 


#ifndef SETUP_H_
#define SETUP_H_
#include <avr/io.h>


#define F_CPU 8000000UL
#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define set_bit(reg,bit) (reg |= (1 << bit))
#define clear_bit(reg,bit) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))

#endif /* SETUP_H_ */