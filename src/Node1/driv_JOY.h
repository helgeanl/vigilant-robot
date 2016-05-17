/*
 * driv_JOY.h
 *
 * Created: 10.09.2015 14:21:26
 *  Author: helgeanl
 */ 


#ifndef DRIV_JOY_H_
#define DRIV_JOY_H_
#include "driv_CAN.h"

typedef struct {
	int8_t x;
	int8_t y;
}joy_position_t;

typedef enum {
	NEUTRAL = 0,
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
}joy_direction_t;

#define LEFT_BUTTON 1
#define RIGHT_BUTTON 2
#define JOY_BUTTON 3

// Joystick interface
void            joy_init();
void            joy_calibrate();
uint8_t         joy_button(uint8_t button); // Returns "BOOL"
joy_position_t  joy_get_position(); // eg. X: 83%, Y: -21%
joy_direction_t joy_get_direction(); // LEFT



#endif /* DRIV_JOY_H_ */