#include "PID_v1.h"
#include "Wire.h"
#include "driv_motor.h"
#include <Arduino.h>


#define SAMPLE_TIME 100
static long             g_current_position;
static uint8_t          g_pos;
static long             g_last_position;


//Define Variables we'll be connecting to
double setpoint, input, output;

//Specify the links and initial tuning parameters
double kp=0.4 , ki=0, kd=0;
PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

#define MAX_RIGHT -9400
int max_right;

 
/* Connectors
 * - Gnd    =   MJ1:PIN2  - Commen Ground
 * - !OE    =   MJ1:PIN3  - Active low output enable of encoder
 * - !RST   =   MJ1:PIN4  - Active low reset of encoder     
 * - SEL    =   MJ1:PIN5  - Select Hi/Lo byte of encoder 
 * - EN     =   MJ1:PIN6  - Enables motor
 * - DIR    =   MJ1:PIN7  - Sets the direction
 * 
 * - DA1    =   MJEX:PIN1 - Analog input
 * - Gnd    =   MJEX:PIN2 - Common ground
 * 
 * - Gns    =   MJ2:PIN2  - Common ground
 * - DO0    =   MJ2:PIN3  - Output bit 0
 * - ...
 * - DO7    =   MJ2:PIN10  - Output bit 7
 */

void motor_init(){
    Wire.begin(); // join i2c bus (address optional for master)
    pinMode(OE, OUTPUT);
    pinMode(SEL, OUTPUT);
    pinMode(RST, OUTPUT);
    pinMode(EN, OUTPUT);
    pinMode(DIR, OUTPUT);
    pinMode(29,INPUT);



    // Calibrate encoder
    motor_set_speed(-40);
    delay(1000);
    digitalWrite(RST, LOW); //  Reset encoder  
    delayMicroseconds(20); 
    digitalWrite(RST, HIGH);  
    digitalWrite(OE, HIGH); // Disable encoder output
    //motor_set_speed(40);
    //delay(1000);
    motor_set_speed(0);
    max_right = -9300;
    delay(200);
       
    g_current_position = motor_read_encoder();
    Serial.print("ENCODER ");
    Serial.print(g_current_position);
    Serial.print("\n");

    
    g_pos = map(g_current_position,0,max_right,0,255);
    
    //initialize the variables we're linked to
    input  = g_pos;
    output = 0;
    setpoint = 0;
    //turn the PID on
    myPID.SetOutputLimits(-100, 100);
    myPID.SetMode(AUTOMATIC);
    //motor_set_position(127);
    g_current_position=motor_read_encoder();
    Serial.print("ENCODER after ");
    Serial.print(g_current_position);
    Serial.print("\n");
  
}

int motor_read_encoder(){
    int data;
    digitalWrite(OE, LOW); // Enable encoder
    digitalWrite(SEL, LOW); // Get high byte
    delayMicroseconds(20);
    data = (int)motor_read_encoder_byte() << 8;
    digitalWrite(SEL, HIGH); // Get low byte
    delayMicroseconds(20); 
    data |= (int)motor_read_encoder_byte();
    digitalWrite(RST, LOW); // Toogle Reset encoder  
    delayMicroseconds(20); 
    digitalWrite(RST, HIGH);
    digitalWrite(OE, HIGH); // Disable encoder 
    Serial.print(data);
    return data;
 }

uint8_t motor_read_encoder_byte(){
    uint8_t temp_byte;
    uint8_t i;
    uint8_t j =7;
    for(i =0; i < 8; i++){
        temp_byte |= (digitalRead(DO7 + i)  << j); // MSB:DO7, LSB:DO0
        j--;
    }
    delayMicroseconds(20);
    return temp_byte;
}

void motor_set_speed(int8_t val){
    uint8_t data;
    digitalWrite(EN, HIGH);			// Enable motor

    if(val >= 0){
        data = map(val,0,100,0,255);
        digitalWrite(DIR, HIGH);	// Set direction right
    }
    else if (val < 0){
        data = map(val,0,-100,0,255);
        digitalWrite(DIR, LOW);		// Set direction left
    }
    Wire.beginTransmission(0x2F);	// transmit to device 0x2F
    Wire.write(0x00);				// Select Output 0
    Wire.write(data);				// V_out = V_ref(val/256)
    Wire.endTransmission();			// stop transmitting
}

void motor_set_position(uint8_t pos){
    setpoint = pos;
    g_current_position += motor_read_encoder();
    input  = map(g_current_position,0,max_right,0,255);
    myPID.Compute();
    motor_set_speed(output);
}

void motor_speed_map(uint8_t x){
    if(x > 110  && x < 140){
        motor_set_speed(0);
    }
    else if(x < 110  && x > 10){
        motor_set_speed(-30);
    }
    else if (x <= 10 ){
        motor_set_speed(-60);
    }
    else if (x >= 140 && x < 245){
        motor_set_speed(30);
    }
    else if (x >= 245 ){
        motor_set_speed(60);
    }

}

void motor_stop(){
    motor_set_speed(0);
    digitalWrite(EN, LOW); // Disable motor
}

