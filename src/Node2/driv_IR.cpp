#include "driv_IR.h"
#include "avr/io.h"
#include "arduino.h"

static uint8_t score;

//void IR_init(){
//  pinMode(IRpin, INPUT);
//}

uint8_t IR_is_broken(uint8_t pin){
    if (analogRead(pin)<40){
        return 1;
    }
    else{
        return 0;
    }
}


