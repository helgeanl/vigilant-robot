/*
 * driv_CAN.h
 *
 * Created: 01.10.2015 11:17:26
 *  Author: helgeanl
 */ 


#ifndef DRIV_CAN_NODE3_H_
#define DRIV_CAN_NODE3_H_
#include <avr/io.h>

typedef struct{
    uint16_t id;
    uint8_t data_length;
    uint8_t data[8];
} can_message_t;

// Available addresses: 352, 416, 800,832
#define RESET_ID        256
#define STATE_ID        288
#define MENU_ID         320
#define SCORE_ID        352
#define GAME_ID         384
#define CONTROLLER_ID   416
#define SOUND_ID        448
#define JOY_ID          2048
#define SLIDER_ID       2176

//High level functions
void    can_init();
void    can_message_send(can_message_t* msg);
uint8_t can_transmit_complete();
void    can_message_receive(can_message_t* message);
void can_int_vect();
uint8_t can_get_rx_flag();

#endif /* DRIV_CAN_NODE3_H_ */