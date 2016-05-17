//
//  fsm.h
//  
//
//  Created by Helge-André Langåker on 30.10.2015.
//
//

#ifndef fsm_h
#define fsm_h

#include <stdio.h>
#include "driv_JOY.h"

void fsm_init();
void fsm_joy_up();
void fsm_joy_down();
void fsm_joy_left();
void fsm_joy_right();
void fsm_joy_button();
void fsm_left_button();
void fsm_right_button();

void fsm_refresh_screen();
void fsm_send_position();

#endif /* fsm_h */
