// ATMega2560 pin mapping
// https://www.arduino.cc/en/Hacking/PinMapping2560

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  Node2 - Arduino sketch of Node 2 main file
//  rev.
//
//  2015, Helge-André Langåker, Johan Vårlid
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "driv_motor.h"
#include "driv_servo_node2.h"
#include "driv_CAN_node2.h"
#include "MCP2515.h"
#include "driv_mcp2515_node2.h"
#include "driv_JOY_node2.h"
#include <avr/interrupt.h>

//#include "pong.h"
#include "driv_IR.h"
#include "PS2X_lib.h"


//PS2 pin numbers
#define PS2_DAT  31      
#define PS2_CMD  35  
#define PS2_SEL  34  
#define PS2_CLK  32

#define SOLENOID 12

int error = 0;
byte type = 0;
byte vibrate = 0;
PS2X ps2x;
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

#define JOYSTICK 1
#define PLAYSTATION 2

uint8_t x;
uint8_t y;
can_message_t send_msg;
can_message_t received_msg;

#define STATE_MENU  1
#define STATE_GAME  2
#define STATE_CALIBRATE  3
#define STATE_DEBUG  4
#define STATE_PID  5
#define STATE_GAME_OVER  6

static int pos;
static uint8_t g_state;
static uint8_t g_game_controller;
static uint8_t current_goal_status;
static uint8_t previous_goal_status=0;
static uint8_t current_loss_status;
static uint8_t previous_loss_status=0;


// Setting up our devices and I/Os
void setup() {
    /************************************************************************/
    /*                      Initialize drivers                              */
    /************************************************************************/
    // Inits the UART
    Serial.begin(57600);
    sei();
    can_init();
    servo_init();
    motor_init();
    
    pinMode(DD_INT, INPUT);
    pinMode(IR_PIN_FRONT, INPUT);
    pinMode(IR_PIN_BACK, INPUT);
    pinMode(SOLENOID, OUTPUT);
    digitalWrite(SOLENOID,HIGH);
    
    g_state = STATE_MENU;
    g_game_controller = JOYSTICK;

    /************************************************************************/
    /*                      Initialize PS2 controller                       */
    /************************************************************************/
    delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
    
    //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
    if(error == 0){
        Serial.print("Found Controller, configured successful ");
        Serial.print("pressures = ");
        if (pressures)
            Serial.println("true ");
        else
            Serial.println("false");
            Serial.print("rumble = ");
        if (rumble)
            Serial.println("true)");
        else
            Serial.println("false");
        Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
        Serial.println("holding L1 or R1 will print out the analog stick values.");
        Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
    }  
    else if(error == 1)
        Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
    else if(error == 2)
        Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

    else if(error == 3)
        Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

    type = ps2x.readType(); 
    switch(type) {
        case 0:
            Serial.print("Unknown Controller type found ");
            break;
        case 1:
            Serial.print("DualShock Controller found ");
            break;
        case 2:
            Serial.print("GuitarHero Controller found ");
            break;
        case 3:
            Serial.print("Wireless Sony DualShock Controller found ");
            break;
    }
    Serial.print("Setup complete\n");

}

void loop() {
    
    switch (g_state) {
        case STATE_MENU:
            break;
        case STATE_GAME:
            if(g_game_controller == PLAYSTATION)
            {
                Serial.print("PS2\n");
                ps2x.read_gamepad(false, vibrate);
               
                motor_speed_map(ps2x.Analog(PSS_LX));
                servo_joy(ps2x.Analog(PSS_RX));
                
                if(ps2x.ButtonPressed(PSB_L1) || ps2x.ButtonPressed(PSB_R1)){ //Shoot with solenoid
                    digitalWrite(SOLENOID,LOW);
                    delay(150);
                    digitalWrite(SOLENOID,HIGH);
                }
            }
            current_goal_status=IR_is_broken(IR_PIN_FRONT);
            if((current_goal_status!=previous_goal_status) && (current_goal_status)){
                Serial.print("Goal!\n");
                send_msg.id = SCORE_ID;
                send_msg.data_length =1;
                send_msg.data[0] = 1; // Add score
                can_message_send(&send_msg);
            }
            previous_goal_status=current_goal_status;
            
            current_loss_status=IR_is_broken(IR_PIN_BACK);
            if((current_loss_status!=previous_loss_status) && (current_loss_status)){
                Serial.print("Life lost\n");  
                send_msg.id = SCORE_ID;
                send_msg.data_length =1;
                send_msg.data[0] = 0; // Add score
                can_message_send(&send_msg);
            }
            previous_loss_status=current_loss_status;
            break;
        case STATE_CALIBRATE:
            break;
        case STATE_DEBUG:
            break;
        case STATE_PID:
            break;
        default:
            break;
    }

    
  if(mcp2515_read(MCP_CANSTAT) & 0x0C || mcp2515_read(MCP_CANSTAT) & 0x0E){   
        can_message_receive(&received_msg);
        Serial.print("CAN\n");
        delay(20);  
        switch (received_msg.id) {
            case JOY_ID:
                if(g_state == STATE_GAME){
                    servo_joy(received_msg.data[0]);
                    if(received_msg.data[1] == 1){
                        digitalWrite(SOLENOID,LOW);
                        delay(150);
                        digitalWrite(SOLENOID,HIGH);
                    }
                }   
                break;
            case SLIDER_ID:
                if(g_state == STATE_GAME){
                    motor_set_position(received_msg.data[0]);
                }   
                break;                
            case CONTROLLER_ID:
                g_game_controller = received_msg.data[0];
                Serial.print("Controller: ");
                Serial.print(g_game_controller);
                Serial.print("\n");
                break;
            case STATE_ID:
                g_state = received_msg.data[0];
                if( g_state == STATE_MENU){
                    servo_position(128);
                    motor_stop();
                }
                else if(g_state == STATE_GAME){
                    Serial.print("State4 game\n");
                }
                else if(g_state == STATE_GAME_OVER){
                    motor_stop;
                }
                else if(received_msg.data[0] == STATE_DEBUG){
                    pos = motor_read_encoder();
                    Serial.print("Encoder pos: ");
                    Serial.print(pos);
                    Serial.print("\n");
                }
                break;                
            default:
                break;
        }
    }
    delay(10);
}

