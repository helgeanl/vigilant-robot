/*
 * setup.h
 *
 * Created: 15.09.2015 13:02:44
 *  Author: Johan Vårlid
 */ 


#ifndef SETUP_H_
#define SETUP_H_

//Setup for the OSC fq which is then set to be the CPU fq
#define F_OSC   4915200
#define F_CPU   F_OSC
#define BAUD    9600
#define MYUBRR (F_OSC-250)/16/BAUD-1

//Added from the project description to help setting bits in registers
#define set_bit(reg,bit) (reg |= (1 << bit))
#define clear_bit(reg,bit) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))



#endif /* SETUP_H_ */
