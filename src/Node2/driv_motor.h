#ifndef DRIV_MOTOR_H_
#define DRIV_MOTOR_H_

#include <Arduino.h>

#define OE          A7  // PF7-A7
#define RST         A6  // PF4-A6
#define SEL         A5  // PF5-A5
#define EN          A4  // PF4-A4
#define DIR         A3  // PF3-A3
#define DO0         A15 // 
#define DO7         A8
#define END_TRIGGER 28  // PA6

void    motor_init();
int     motor_read_encoder();
uint8_t motor_read_encoder_byte();
void    motor_set_speed(int8_t val);
void    motor_set_position(uint8_t pos);
void    motor_speed_map(uint8_t x);
void    motor_stop();

#endif /* DRIV_MOTOR_H*/
