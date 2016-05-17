// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  fsm.c - FSM for game logic, handles all triggered events
//  rev.
//
//  2015, Helge-André Langåker, Johan Vårlid
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

#include "fsm.h"
#include "menu.h"
#include "driv_OLED.h"
#include "driv_JOY.h"
#include "driv_ADC.h"
#include "driv_CAN.h"
#include "setup.h"


#define STATE_MENU       1
#define	STATE_GAME       2
#define	STATE_CALIBRATE  3
#define	STATE_DEBUG      4
#define	STATE_PID        5
#define	STATE_GAME_OVER  6

#define JOYSTICK    1
#define PLAYSTATION 2

#define MENU_SOUND    7
#define STARTUP_SOUND 6


// ------- Private variable --------
static uint8_t			g_game_melody;
static uint8_t          g_state;
static uint8_t          g_score;
static uint8_t          g_game_controller;
static can_message_t    g_can_msg;



// ------- Prototype private functions -------
static void play_melody(uint8_t song);
static void send_state(uint8_t state);
static void send_controller(uint8_t controller);
static void add_score();
static void reset_score();
static void print_score();
static void new_game(uint8_t controller);

// ------- Public functions -------

void fsm_init(){
	oled_print_pong();
    g_game_melody = 1;
	g_score = 0;
	g_state = STATE_MENU;
	
	// Play start-up tune
    play_melody(STARTUP_SOUND);
	_delay_ms(5000);
	
	menu_init();
	menu_print();
	menu_print_arrow();
}

void fsm_joy_up(){
    switch (g_state) {
        case STATE_MENU:
            if(menu_get_choices() != 0){
				if(menu_get_arrow_position() != 1){
                    play_melody(MENU_SOUND);
				}
                menu_set_arrow_position(menu_get_arrow_position() -1);
                menu_print_arrow();
            }
            break;
        case STATE_GAME:
            break;
        case STATE_GAME_OVER:
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
}
void fsm_joy_down(){
    switch (g_state) {
        case STATE_MENU:
            if(menu_get_choices() > menu_get_arrow_position()){
                menu_set_arrow_position(menu_get_arrow_position() +1);
                menu_print_arrow();
                play_melody(MENU_SOUND);
            }
            break;
        case STATE_GAME:
            break;
		case STATE_GAME_OVER:
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
}
void fsm_joy_left(){
    switch (g_state) {
        case STATE_MENU:
            if(menu_back()){
                play_melody(MENU_SOUND);
            }
            break;
        case STATE_GAME:
            break;
        case STATE_GAME_OVER:
			g_state = STATE_MENU;
			menu_home();
			break;
		case STATE_CALIBRATE:
            break;
        case STATE_DEBUG:
            menu_back();
			g_state = STATE_MENU;
            break;
        case STATE_PID:
            g_state = STATE_MENU;
            break;
        default:
            break;
    }
}
void fsm_joy_right(){
    switch (g_state) {
        case STATE_MENU:
            if(menu_next()){
                play_melody(MENU_SOUND);
			}
            if(menu_get_index() == 0){
                if(menu_get_arrow_position == 2){
                    oled_print_pong();
                }
                else if(menu_get_arrow_position() == 3){
                    oled_print_game_over();
                }
            }
            else if(menu_get_index() == 4){
                g_state = STATE_CALIBRATE;
            }
			else if(menu_get_index() == 6){
				g_state = STATE_DEBUG;
			}
			else if(menu_get_index() == 7){
				g_game_melody = menu_get_arrow_position();
				play_melody(g_game_melody);
			}
			else if(menu_get_index() == 2){
				new_game(JOYSTICK);
			}
			else if(menu_get_index() == 3){
				new_game(PLAYSTATION);
			}
            break;
        case STATE_GAME:
            break;
        case STATE_GAME_OVER:
			break;
		case STATE_CALIBRATE:
            break;
        case STATE_DEBUG:
			if(menu_get_arrow_position() == 1){
				send_state(STATE_DEBUG);
				printf("Debug Mode\n");
			}
            break;
        case STATE_PID:
            
            break;
        default:
            break;
    }
}

void fsm_left_button(){
    switch (g_state) {
        case STATE_MENU:
            if(menu_home()){
                play_melody(MENU_SOUND);
            }
			g_state = STATE_MENU;
            break;
        case STATE_GAME:
			menu_home();
			g_state = STATE_MENU;
            play_melody(MENU_SOUND);
			_delay_ms(50);
			send_state(g_state);
            break;
        case STATE_GAME_OVER:
			break;
		case STATE_CALIBRATE:
            menu_home();
			g_state = STATE_MENU;
            break;
        case STATE_DEBUG:
            menu_home();
			g_state = STATE_MENU;
            break;
        case STATE_PID:
            break;
        default:
            break;
    }
}

void fsm_right_button(){
    switch (g_state) {
        case STATE_MENU:
			if(menu_next()){
                play_melody(MENU_SOUND);
			}
			_delay_ms(50);
  
            if(menu_get_index() == 0){
                if(menu_get_arrow_position == 2){
                    oled_print_pong();
                }
                else if(menu_get_arrow_position() == 3){
                    oled_print_game_over();
                }
            }
            else if(menu_get_index() == 4){
                g_state = STATE_CALIBRATE;
            }
            else if(menu_get_index() == 6){
                g_state = STATE_DEBUG;
            }
            else if(menu_get_index() == 7){
                g_game_melody = menu_get_arrow_position();
                play_melody(g_game_melody);
            }
            else if(menu_get_index() == 2){
                new_game(JOYSTICK);
            }
            else if(menu_get_index() == 3){
                new_game(PLAYSTATION);
            }
            break;
        case STATE_GAME: // Send pulse to solenoid
            set_bit(DDRD, PD4);
            _delay_ms(200);
            clear_bit(DDRD,PD4);
            break;
        case STATE_GAME_OVER:
			break;
		case STATE_CALIBRATE:
			joy_calibrate();
            break;
        case STATE_DEBUG:
            if(menu_get_arrow_position() == 1){
                send_state(STATE_DEBUG);
                printf("Debug Mode\n");
            }
            break;
        case STATE_PID:
            
            break;
        default:
            break;
    }
}


void fsm_joy_button(){
    switch (g_state) {
        case STATE_MENU:
            break;
        case STATE_GAME:
			set_bit(DDRD, PD4);
			_delay_ms(200);
			clear_bit(DDRD,PD4); 
            break;
        case STATE_GAME_OVER:
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
}

void fsm_can(can_message_t *msg){
    switch (msg->id) {
        case MENU_ID:
            g_state = msg->data[0];
            break;
        case GAME_ID:
            break;
		case SCORE_ID:
			if(msg->data[0]){
				add_score();
				print_score();
			}
			else{
				g_state = STATE_GAME_OVER;
				oled_print_game_over();
				play_melody(0);
			}
			break;
        case CONTROLLER_ID:
            break;
        case SLIDER_ID:
            if(g_state == STATE_CALIBRATE){
                oled_pos(3,8);
                fprintf(FONT5,"Left: %d %%    \nRight: %d %%    ", msg->data[0], msg->data[1]);
            }
            break;
        default:
            break;
    }
}

void fsm_refresh_screen(){
	fsm_send_position();
	joy_position_t joy_pos;
    switch (g_state) {
        case STATE_MENU:
            break;
        case STATE_GAME:
			if(g_game_controller == JOYSTICK)
			{
				fsm_send_position();
			}
            break;
        case STATE_GAME_OVER:
			break;
		case STATE_CALIBRATE:
            joy_pos = joy_get_position();
            oled_pos(1,8);
            fprintf(FONT5,"X: %d %%    \nY: %d %%    ", joy_pos.x, joy_pos.y);
            //fprintf(FONT5,"X: %d %%    \nY: %d %%    \nLeft: %d    \nRight: %d    ",
            //        joy_pos.x, joy_pos.y, adc_read(4), adc_read(3));
            break;
        case STATE_DEBUG:
            break; 
        case STATE_PID:
            break;
        default:
            break;
    }
}



// ------ Private functions ------

void fsm_send_position(){
    g_can_msg.id           = SLIDER_ID;
    g_can_msg.data_length  = 1;
	g_can_msg.data[0]      = 15; // ?????
   // g_can_msg.data[0]      = adc_read(1); // joy y
    //g_can_msg.data[1]      = adc_read(2); // joy x
    //g_game_msg.data[3]      = adc_read(3); // right slider
    //g_game_msg.data[4]      = adc_read(4); // left slider
    can_message_send(&g_can_msg);
}
 

/* Melody:
 // Stop melody = 0
 // Mario = 1
 // Underworld = 2
 // Imperial march = 3
 // Sorcerers apprentice = 4
 // Fuer Elise = 5
 // Menu sound = 6
 // Start sound = 7
 */
static void play_melody(uint8_t song){
    if((song >= 0) && (song <=7)){
        g_can_msg.id            = SOUND_ID;
        g_can_msg.data_length   = 1;
        g_can_msg.data[0]       = song;
        can_message_send(&g_can_msg);
    }
}

static void send_state(uint8_t state){
    g_can_msg.id            = MENU_ID;
    g_can_msg.data_length   = 1;
    g_can_msg.data[0]       = state;
    can_message_send(&g_can_msg);
}
static void send_controller(uint8_t controller){
	g_can_msg.id            = CONTROLLER_ID;
	g_can_msg.data_length   = 1;
	g_can_msg.data[0]       = controller;
	can_message_send(&g_can_msg);
}
static void add_score(){
	g_score++;
}
static void reset_score(){
	g_score = 0;
}
static void print_score(){
	oled_pos(4,36);
	fprintf(FONT5, "%d  ", g_score);
}
static void new_game(uint8_t controller){
	g_state  = STATE_GAME;
	g_game_controller = controller;
	send_controller(g_game_controller);
	play_melody(g_game_melody);
	reset_score();
	print_score();
	send_state(g_state);
}