
/*
 * driv_CAN.h
 *
 * Created: 01.10.2015 11:17:26
 *  Author: helgeanl
 */ 


#ifndef DRIV_CAN_H_
#define DRIV_CAN_H_
#include <avr/io.h>

// Message
typedef struct{
    uint16_t id;
	uint8_t data_length;
	uint8_t data[8];
} can_message_t;

// CAN IDs
#define JOY_ID          256
#define RESET_ID        288
#define SOUND_ID        352
#define SLIDER_ID       320
#define STATE_ID        384
#define SCORE_ID        416
#define MENU_ID         448
#define GAME_ID         480
#define CONTROLLER_ID   768

/**
 Initialize CAN
 */
void    can_init();

/**
 Send CAN message
 @param message pointer, pointer to CAN message
 */
void    can_message_send(can_message_t* msg);

/**
 Read value of ADC channel
 @return
 */
uint8_t can_transmit_complete();
void    can_message_receive(can_message_t* message);


#endif /* DRIV_CAN_H_ */