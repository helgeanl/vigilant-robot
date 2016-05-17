//
//  driv_JOY_arduino.c
//  
//
//  Created by Helge-André Langåker on 22.10.2015.
//
//

#include "driv_JOY_node2.h"
#include "driv_CAN_node2.h"


void recieve_position(can_message_t *joy_pos_msg, joy_position_t *joy_pos){
    // Check if CAN message content is joy position
    if(joy_pos_msg->id == JOY_ID){
        joy_pos->x = joy_pos_msg->data[0];
        joy_pos->y = joy_pos_msg->data[1];
    }
}


