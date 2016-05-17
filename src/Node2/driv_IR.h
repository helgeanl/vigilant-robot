
#ifndef DRIV_IR_H_
#define DRIV_IR_H_

#define IR_PIN_FRONT A0 // PF0
#define IR_PIN_BACK A1  // PF1

#include "avr/io.h"


uint8_t IR_is_broken(uint8_t pin); //Returns 1 if the light is broken.
//void IR_init();

#endif /* DRIV_IR_H*/
