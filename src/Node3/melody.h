/*
 * melody.h
 *
 * Created: 08.11.2015 00:24:50
 *  Author: johanvaa
 */ 


#ifndef MELODY_H_
#define MELODY_H_

#define MELODY_PIN PB7

#define PAUSE	 0//pause = silence
#define NOTE_B3  253
#define NOTE_C4  239
#define NOTE_CS4 225
#define NOTE_D4  213
#define NOTE_DS4 201
#define NOTE_E4  190
#define NOTE_F4  179
#define NOTE_FS4 169
#define NOTE_G4  159
#define NOTE_GS4 150
#define NOTE_A4  142
#define NOTE_AS4 134
#define NOTE_B4  127
#define NOTE_C5  119
#define NOTE_CS5 113
#define NOTE_D5  106
#define NOTE_DS5 100
#define NOTE_E5  95
#define NOTE_F5  89
#define NOTE_FS5 84
#define NOTE_G5  80
#define NOTE_GS5 75
#define NOTE_A5  71
#define NOTE_AS5 67
#define NOTE_B5  63
#define NOTE_C6  60
#define NOTE_CS6 56
#define NOTE_D6  53
#define NOTE_DS6 50
#define NOTE_E6  47
#define NOTE_F6  45
#define NOTE_FS6 42
#define NOTE_G6  40
#define NOTE_GS6 38
#define NOTE_A6  36
#define NOTE_AS6 34
#define NOTE_B6  32
#define NOTE_C7  30
#define NOTE_E7  24
#define NOTE_F7  22
#define NOTE_G7  20
#define NOTE_A7  19

//Note durations
#define WHOLE	  32
#define HALF	  16
#define THIRD	  12
#define QUATER	  8
#define SIXTH	  6
#define EIGHTH	  4
#define TWELVETH  3 
#define SIXTEENTH 2
#define BREAK     1

void melody_init();
void melody_play(int song);
void melody_stop();
uint8_t melody_get_play_tune();

// Mario = 1
// Underworld = 2
// Imperial march = 3
// Sorcerers apprentice = 4
// Fuer Elise = 5
// Menu sound = 6
// Start sound = 7


#endif /* MELODY_H_ */