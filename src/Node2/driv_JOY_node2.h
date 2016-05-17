//
//  driv_JOY_arduino.h
//  
//
//  Created by Helge-André Langåker on 22.10.2015.
//
//

#ifndef driv_JOY_arduino_h
#define driv_JOY_arduino_h

#include "driv_CAN_node2.h"
#include <stdio.h>

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



void joy_recieve_position( can_message_t *joy_pos_msg, joy_position_t * joy_pos);


#endif /* driv_JOY_arduino_h */
