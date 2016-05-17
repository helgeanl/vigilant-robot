/*
 * melody.c
 *
 * Created: 08.11.2015 00:14:49
 *  Author: johanvaa
 */ 


#include <avr/io.h>
#include "setup.h"
#include "melody.h"
#include <util/delay.h>
#include <avr/interrupt.h>

uint16_t play_tune,*tune_array;
unsigned int tempo;
unsigned int ms_tick=0;  //general purpose millisecond timer tick, incremented by TIMER2
int song = 0;

void melody_init(){
	DDRB |= (1<<PB7);				//set data direction reg bit 0 to output
	PORTB &=~(1<<PB7);			//set buzzer output low
	/*
	initialize timer 0
	*/
	TCCR0A = 0; //tmr0 Clear Timer on Compare Match
	TCCR0B = _BV(WGM01)|_BV(CS01)|_BV(CS00);  //CTC mode with CPU clock/64 = 125 kHz
	OCR0A = 125;  //set for 1 ms interrupt
	OCR0B = 126;
	TCNT0=0;
	TIMSK0 = (1<<OCIE0A)|(1<<OCIE0B); // enable interrupt on TCNT2=OCR0A
	/*
	initialize timer 1
	*/
	
	TCCR2A= (1<<WGM21);	//mode 2, clear timer on compare match
	TCCR2B=(1<<CS22);		//CS22=1,CS21=0,CS20=0	=> counter increments at 8 MHz/64 = 125 kHz
	TCNT2=0;				//clear counter
	OCR2A=255;				//set OCR2A to minimum o/p frequency
	OCR2B=255;				//set OCR2B to max, irrelevant
	TIMSK2= (1<<OCIE2A);	//enable interrupt on compare match with OCR2A
	play_tune=0;
}
//Start melody
int start_melody[] = {(1000>>5),
	
	EIGHTH, NOTE_C5, BREAK, PAUSE,EIGHTH, NOTE_D5, BREAK, PAUSE,
	EIGHTH, NOTE_E5, BREAK, PAUSE,EIGHTH, NOTE_F5, BREAK, PAUSE,
	EIGHTH, NOTE_G5, BREAK, PAUSE,EIGHTH, NOTE_A5, BREAK, PAUSE,
	EIGHTH, NOTE_B5, BREAK, PAUSE,WHOLE, NOTE_C6, BREAK, PAUSE,
	0,0
};

//Start tempo

//menu melody
int menu_melody[] = {(200>>5),
	TWELVETH, NOTE_F7,0,0
};

//Mario main theme melody
int mario_melody[] = {(1500>>5),
	TWELVETH, NOTE_E6, TWELVETH, NOTE_E6, TWELVETH, 0, TWELVETH, NOTE_E6,
	TWELVETH, 0, TWELVETH, NOTE_C6, TWELVETH, NOTE_E6, TWELVETH, 0,
	TWELVETH, NOTE_G6, TWELVETH, 0, TWELVETH, 0,  TWELVETH, 0,
	TWELVETH, NOTE_G5, TWELVETH, 0, TWELVETH, 0, TWELVETH, 0,
	
	TWELVETH, NOTE_C6, TWELVETH, 0, TWELVETH, 0, TWELVETH, NOTE_G5,
	TWELVETH, 0, TWELVETH, 0, TWELVETH, NOTE_E5, TWELVETH, 0,
	TWELVETH, 0, TWELVETH, NOTE_A5, TWELVETH, 0, TWELVETH, NOTE_B5,
	TWELVETH, 0, TWELVETH, NOTE_AS5, TWELVETH, NOTE_A5, TWELVETH, 0,
	
	EIGHTH, NOTE_G5, EIGHTH, NOTE_E6, EIGHTH, NOTE_G6,
	TWELVETH, NOTE_A6, TWELVETH, 0, TWELVETH, NOTE_F6, TWELVETH, NOTE_G6,
	TWELVETH, 0, TWELVETH, NOTE_E6, TWELVETH, 0, TWELVETH, NOTE_C6,
	TWELVETH, NOTE_D6, TWELVETH, NOTE_B5, TWELVETH, 0, TWELVETH, 0,
	
	TWELVETH, NOTE_C6, TWELVETH, 0, TWELVETH, 0, TWELVETH, NOTE_G5,
	TWELVETH, 0, TWELVETH, 0, TWELVETH, NOTE_E5, TWELVETH, 0,
	TWELVETH, 0, TWELVETH, NOTE_A5, TWELVETH, 0, TWELVETH, NOTE_B5,
	TWELVETH, 0, TWELVETH, NOTE_AS5, TWELVETH, NOTE_A5, TWELVETH, 0,
	
	EIGHTH, NOTE_G5, EIGHTH,  NOTE_E6, EIGHTH, NOTE_G6,
	TWELVETH, NOTE_A6, TWELVETH, 0, TWELVETH, NOTE_F6, TWELVETH, NOTE_G6,
	TWELVETH, 0, TWELVETH, NOTE_E6, TWELVETH, 0, TWELVETH, NOTE_C6,
	TWELVETH, NOTE_D6, TWELVETH, NOTE_B5, TWELVETH, 0, TWELVETH, 0, 0,0
};
//Underworld melody
int underworld_melody[] = {(1500>>5),
	TWELVETH, NOTE_C5, TWELVETH, NOTE_C6,TWELVETH, NOTE_A4,TWELVETH, NOTE_A5,
	TWELVETH, NOTE_AS4, TWELVETH, NOTE_AS5, SIXTH,0,
	THIRD, 0,
	TWELVETH, NOTE_C5, TWELVETH, NOTE_C6, TWELVETH, NOTE_A4, TWELVETH, NOTE_A5,
	TWELVETH, NOTE_AS4, TWELVETH, NOTE_AS5, SIXTH, 0,
	THIRD, 0,
	TWELVETH, NOTE_F4, TWELVETH, NOTE_F5, TWELVETH, NOTE_D4, TWELVETH, NOTE_D5,
	TWELVETH, NOTE_DS4, TWELVETH, NOTE_DS5, SIXTH, 0,
	THIRD, 0,
	TWELVETH, NOTE_F4, TWELVETH, NOTE_F5, TWELVETH, NOTE_D4, TWELVETH, NOTE_D5,
	TWELVETH, NOTE_DS4, TWELVETH, NOTE_DS5, SIXTH, 0,
	SIXTH, 0, SIXTEENTH, NOTE_DS5, SIXTEENTH, NOTE_CS5, SIXTEENTH, NOTE_D5,
	SIXTH, NOTE_CS5, SIXTH, NOTE_DS5,
	SIXTH, NOTE_CS5, SIXTH, NOTE_GS4,
	SIXTH, NOTE_G4, SIXTH, NOTE_CS5,
	SIXTEENTH, NOTE_C5, SIXTEENTH, NOTE_FS5, SIXTEENTH, NOTE_F5, SIXTEENTH, NOTE_E4, SIXTEENTH, NOTE_AS5, SIXTEENTH, NOTE_A5,
	TWELVETH, NOTE_GS5, TWELVETH, NOTE_DS5, TWELVETH, NOTE_B4,
	TWELVETH, NOTE_AS4, TWELVETH, NOTE_A4, TWELVETH, NOTE_GS4,
	THIRD, 0, THIRD, 0, THIRD, 0 ,0,0
};

int imperial_march_melody[] ={(1500>>5),
	QUATER ,NOTE_A4, BREAK, PAUSE, QUATER ,NOTE_A4, QUATER ,NOTE_A4,SIXTH, NOTE_F4, SIXTEENTH, NOTE_C5,

	QUATER ,NOTE_A4, SIXTH, NOTE_F4, SIXTEENTH, NOTE_C5, HALF, NOTE_A4,

	QUATER ,NOTE_E5, BREAK, PAUSE, QUATER ,NOTE_E5, BREAK, PAUSE, QUATER ,NOTE_E5, SIXTH, NOTE_F5,SIXTEENTH, NOTE_C5,

	QUATER ,NOTE_GS4, SIXTH, NOTE_F4, SIXTEENTH, NOTE_C5, HALF, NOTE_A4,

	QUATER ,NOTE_A5, SIXTH, NOTE_A4, SIXTEENTH, NOTE_A4, QUATER ,NOTE_A5, SIXTH, NOTE_GS5, SIXTEENTH, NOTE_G5,

	SIXTEENTH, NOTE_FS5, SIXTEENTH, NOTE_E5, EIGHTH, NOTE_F5, EIGHTH, PAUSE, EIGHTH, NOTE_AS4, QUATER ,NOTE_DS5, SIXTH, NOTE_D5, SIXTEENTH, NOTE_D5,

	SIXTEENTH, NOTE_C5, SIXTEENTH, NOTE_B4, EIGHTH, NOTE_C5, EIGHTH, PAUSE, EIGHTH, NOTE_F4, QUATER ,NOTE_GS4, SIXTH, NOTE_F4, SIXTEENTH, NOTE_A4,

	QUATER ,NOTE_C5, SIXTH, NOTE_A4, SIXTEENTH, NOTE_C5, HALF, NOTE_E5,

	QUATER ,NOTE_A5, SIXTH, NOTE_A4, SIXTEENTH, NOTE_A4, QUATER ,NOTE_A5, SIXTH, NOTE_GS5, SIXTEENTH, NOTE_G5,

	SIXTEENTH, NOTE_FS5, SIXTEENTH, NOTE_E5, EIGHTH, NOTE_F5, EIGHTH, PAUSE, EIGHTH, NOTE_AS4, QUATER ,NOTE_DS5, SIXTH, NOTE_D5, SIXTEENTH, NOTE_D5,

	SIXTEENTH, NOTE_C5, SIXTEENTH, NOTE_B4, EIGHTH, NOTE_C5, EIGHTH, PAUSE, EIGHTH, NOTE_F4, QUATER ,NOTE_GS4, SIXTH, NOTE_F4, SIXTEENTH, NOTE_A4,
	
	QUATER ,NOTE_A4, SIXTH, NOTE_F4, SIXTEENTH, NOTE_C5, HALF, NOTE_A4,0,0
};
	uint16_t sorcerer_melody[]= //Sorcerer's Apprentice by Paul Dukas.
	{
		(210>>5),
		HALF,NOTE_D5,HALF,PAUSE,HALF,PAUSE,
		HALF,NOTE_A5,HALF,PAUSE,HALF,PAUSE,
		HALF,NOTE_A4,HALF,NOTE_B4,HALF,NOTE_CS5,
		HALF,NOTE_D5,HALF,PAUSE,HALF,NOTE_F5,
		HALF,NOTE_D5,HALF,PAUSE,HALF,NOTE_F5,
		HALF,NOTE_E5,HALF,NOTE_D5,HALF,NOTE_CS5,
		HALF,NOTE_D5,HALF,PAUSE,HALF,NOTE_F5,
		HALF,NOTE_D5,HALF,PAUSE,HALF,NOTE_F5,
		HALF,NOTE_E5,HALF,NOTE_D5,HALF,NOTE_CS5,
		HALF,NOTE_D5,HALF,PAUSE,HALF,NOTE_F5,
		HALF,NOTE_D5,HALF,NOTE_F5,HALF,NOTE_E5,
		HALF,NOTE_D5,HALF,NOTE_E5,HALF,NOTE_F5,
		HALF,NOTE_E5,HALF,NOTE_G5,HALF,NOTE_F5,
		HALF,NOTE_E5,HALF,PAUSE,HALF,NOTE_GS5,
		HALF,NOTE_D5,HALF,PAUSE,HALF,NOTE_F5,
		HALF,NOTE_E5,HALF,NOTE_G5,HALF,NOTE_F5,
		HALF,NOTE_E5,HALF,PAUSE,HALF,NOTE_GS5,
		HALF,NOTE_D5,HALF,PAUSE,HALF,NOTE_F5,
		HALF,NOTE_E5,HALF,NOTE_F5,HALF,NOTE_G5,
		THIRD,NOTE_A5,EIGHTH,PAUSE,THIRD,NOTE_A5,EIGHTH,PAUSE,THIRD,NOTE_A5,EIGHTH,PAUSE,
		THIRD,NOTE_A5,EIGHTH,PAUSE,THIRD,NOTE_A5,EIGHTH,PAUSE,THIRD,NOTE_A5,EIGHTH,PAUSE,
		HALF,NOTE_A5,HALF,NOTE_G5,HALF,NOTE_F5,
		HALF,NOTE_E5,HALF,NOTE_G5,HALF,NOTE_F5,
		HALF,NOTE_E5,HALF,NOTE_D5,HALF,NOTE_C5,
		EIGHTH,NOTE_D5,THIRD,NOTE_C5,HALF,NOTE_B4,HALF,NOTE_A4,
		0,0
	};
	uint16_t fuer_elise_melody[]= //modified from AVR Butterfly code example. Thanks, ATMEL Norway!

	{		(220>>3),
		8,NOTE_E5, 8,NOTE_DS5, 8,NOTE_E5, 8,NOTE_DS5, 8,NOTE_E5, 8,NOTE_B4, 8,NOTE_D5, 8,NOTE_C5,HALF,NOTE_A4, 8,PAUSE,
		8,NOTE_C4, 8,NOTE_E4, 8,NOTE_A4,HALF,NOTE_B4, 8,PAUSE, 8,NOTE_E4, 8,NOTE_GS4, 8,NOTE_B4,HALF,NOTE_C5, 8,PAUSE, 8,NOTE_E4,
		8,NOTE_E5, 8,NOTE_DS5, 8,NOTE_E5, 8,NOTE_DS5, 8,NOTE_E5, 8,NOTE_B4, 8,NOTE_D5, 8,NOTE_C5,HALF,NOTE_A4, 8,PAUSE, 8,NOTE_C4,
		8,NOTE_E4, 8,NOTE_A4,HALF,NOTE_B4, 8,PAUSE, 8,NOTE_E4, 8,NOTE_C5, 8,NOTE_B4,HALF,NOTE_A4,
		8,PAUSE,8,PAUSE,  //up one octave for test!
		8,NOTE_E6, 8,NOTE_DS6, 8,NOTE_E6, 8,NOTE_DS6, 8,NOTE_E6, 8,NOTE_B5, 8,NOTE_D6, 8,NOTE_C6,HALF,NOTE_A5, 8,PAUSE,
		8,NOTE_C4, 8,NOTE_E5, 8,NOTE_A5,HALF,NOTE_B5, 8,PAUSE, 8,NOTE_E5, 8,NOTE_GS5, 8,NOTE_B5,HALF,NOTE_C6, 8,PAUSE, 8,NOTE_E5,
		8,NOTE_E6, 8,NOTE_DS6, 8,NOTE_E6, 8,NOTE_DS6, 8,NOTE_E6, 8,NOTE_B5, 8,NOTE_D6, 8,NOTE_C6,HALF,NOTE_A5, 8,PAUSE, 8,NOTE_C4,
		8,NOTE_E5, 8,NOTE_A5,HALF,NOTE_B5, 8,PAUSE, 8,NOTE_E5, 8,NOTE_C6, 8,NOTE_B5,HALF,NOTE_A5,
		0, 0
	};
	uint16_t game_over_melody[]={(1500>>5),
		EIGHTH, NOTE_C5, SIXTEENTH ,PAUSE ,EIGHTH ,NOTE_G4 ,SIXTEENTH ,PAUSE ,EIGHTH, NOTE_E4 ,EIGHTH ,PAUSE ,
		EIGHTH,NOTE_A4,SIXTEENTH,PAUSE,EIGHTH,NOTE_B4,SIXTEENTH,PAUSE,EIGHTH,NOTE_A4,SIXTEENTH,PAUSE,
		EIGHTH,NOTE_GS4,SIXTEENTH,PAUSE,EIGHTH,NOTE_AS4,SIXTEENTH,PAUSE,EIGHTH,NOTE_GS4,SIXTEENTH,PAUSE,
		SIXTEENTH,NOTE_E4,SIXTEENTH,PAUSE,SIXTEENTH,NOTE_D4,SIXTEENTH,PAUSE,HALF,NOTE_E4,
		0,0
	};
	
	void melody_buzz(int song[]) {
		play_tune=1;
		tempo=song[0];
		tune_array=&song[1];
		
	}
	
void melody_play(int song) {
	// iterate over the notes of the melody:
	if (song == 2) {
		melody_buzz(underworld_melody);
		
	}
	else if(song==3){
		melody_buzz(imperial_march_melody);
		
	}
    else if (song==4){
        melody_buzz(sorcerer_melody);
    }
    else if (song==5){
        melody_buzz(fuer_elise_melody);
    }
	else if(song==6){
		melody_buzz(start_melody);

	}
	else if(song==7){
		melody_buzz(menu_melody);
	}
	else if (song==8)
	{
		melody_buzz(game_over_melody);
	}
	else {
		melody_buzz(mario_melody);
	}
}



void melody_stop(){
	play_tune=0;
}

uint8_t melody_get_play_tune(){
	return play_tune;
}

ISR(TIMER2_COMPA_vect)
{
	PORTB ^= (1 << PB7);					//toggle buzzer output line
}


/*
TIMER 0 OCR0A interrupt service routine
This routine is called every millisecond, when TCNT0 = OCR0A (125)

Operation:
-increment general purpose timer tick at 1 ms intervals
-if tempo>0, continue playing current tune, pointed to by *tune_array
-signals "done playing tune" by setting global variable play_tune->0
*/

ISR(TIMER0_COMPA_vect)
{

	static uint16_t duration=0;	//internal timer for current note
	volatile uint16_t dur,note;

	ms_tick++;								//increment timer tick at 1 ms intervals

	if(play_tune) {							//are we playing a tune?
		if(duration>0)	duration--;				//yes, count down this note's timer

		else {								//done with this note, get next [duration,note] pair
			dur=*tune_array++;
			duration = tempo*dur; 			//calculate time in ms to play this note
			if(dur==0) play_tune=0;		//duration entry=0, so signal done playing tune
			note=*tune_array++;
			if (note>0) {				//check for note or silence to play
				OCR2A = note;			//set timer interrupt period and point to next entry in tune table
				DDRB |= (1<<PB7); 				//turn on buzzer output line
			}
			else {
				OCR2A=255;				//silence, reduce interrupt load
				DDRB &=~(1<<PB7); 			//and turn off buzzer
			}
		}
	}
}

