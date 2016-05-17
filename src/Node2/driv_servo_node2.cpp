
//#include "C:\Program Files (x86)\Arduino\libraries\Servo\src\Servo.h"
//#include <time.h>

#include"arduino.h"
#include"Servo.h" 


Servo myservo;  // create servo object to control a servo 
              
static int servo_pos;

void servo_init(){
    myservo.attach(9,1000,2000);  // attaches the servo on pin 9 to the servo object 
    servo_pos = 1500;
}

void servo_joy(uint8_t x){
    x = map(x,0,255,255,0);
    if(x < 110  && servo_pos >= 1050){
        servo_pos -= 80;
    }
    else if (x >= 150 && servo_pos <= 1950){
        servo_pos += 80;
    }
    myservo.write(servo_pos);
    delay(5);
}

void servo_position(uint8_t x){
    if(myservo.read() != x){
        int pos = map(x,0,255,1000,2000);
        myservo.write(pos);
        delay(15);
    }
}


