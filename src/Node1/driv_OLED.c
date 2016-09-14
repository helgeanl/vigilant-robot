/*
 * OLED.c
 *
 * Created: 17.09.2015 12:22:09
 *  Author: helgeanl
 */ 
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "driv_OLED.h"
#include "fonts.h"


volatile uint8_t *oled_c = (uint8_t *) 0x1000; // Command 
volatile uint8_t *oled_d = (uint8_t *) 0x1200; // Data
static uint8_t oled_current_line_num;


//------------------------------------------------------------

uint8_t oled_get_current_line(){
	return oled_current_line_num;
}

void oled_init()
{	
	oled_write_c(0xae); 	// display off
	oled_write_c(0xa1); 	// segment remap
	oled_write_c(0xda); 	// common pads hardware: alternative
	oled_write_c(0x12);
	oled_write_c(0xc8); 	// common output scan direction:com63~com0
	oled_write_c(0xa8); 	// multiplex ration mode:63
	oled_write_c(0x3f);
	oled_write_c(0xd5); 	// display divide ratio/osc. freq. mode
	oled_write_c(0x80);
	oled_write_c(0x81); 	// contrast control
	oled_write_c(0x50);
	oled_write_c(0xd9); 	// set pre-charge period
	oled_write_c(0x21);
	oled_write_c(0x20); 	// Set Memory Addressing Mode
	oled_write_c(0x02);
	oled_write_c(0xdb); 	// VCOM deselect level mode
	oled_write_c(0x30);
	oled_write_c(0xad); 	// master configuration
	oled_write_c(0x00);
	oled_write_c(0xa4); 	// out follows RAM content
	oled_write_c(0xa6); 	// set normal display
	oled_write_c(0xaf); 	// display on
	oled_reset();
}
/* Write command */
void oled_write_c(uint8_t command){
	oled_c[0] = command;
}
/* Write data*/
void oled_write_d(uint8_t data){
	oled_d[0] = data;
}

/* Clear the screen */
void oled_reset(){
	for(int line=0;line<8;line++){
		oled_clear_line(line);
	}
}
/* Clear one line */
void oled_clear_line(uint8_t line){ 		
	oled_write_c(0xb0 + line); 		// selects row/page
	for(int byte=0;byte<128;byte++){
		oled_d[byte]=0x00;		// Clear current column
	}
}

/* Go to given row*/
void oled_goto_line(uint8_t line){
	oled_write_c(0xb0 + line);
	oled_current_line_num = line;
}

/* Go to given row and column*/
void oled_pos(uint8_t row, uint8_t col){
	oled_write_c(0xb0 + row);			// Go to row/page
	oled_current_line_num = row;
	oled_write_c(0x00 + (col & 0x0F));          	// Low column start address
	oled_write_c(0x10 + ((col >> 4) & 0x0F));	// High column start address
}

/* Write a character to the screen with font 4 to current position*/
int oled_putchar4(char character, FILE *stream){ 	// Use ASCII code minus 32, Font4
	if(character == '\n'){
		oled_pos(oled_current_line_num +1, 8);	// Next line with column margin of 8
		return 0;
	}
	for(uint8_t i = 0; i < 4; ++i){
		oled_write_d(pgm_read_word(&font4[character - 32][i]));
	}
	oled_write_d(0x00);
	return 0;
}

/* Write a character to the screen with font 5 to current position */
int oled_putchar5(char character, FILE *stream){ // Use ASCII code minus 32, Font5
    if(character == '\n'){
	    oled_pos(oled_current_line_num +1, 8);
		return 0;
    }
	for(uint8_t i = 0; i < 5; ++i){
        oled_write_d(pgm_read_word(&font5[character - 32][i]));
    }
	oled_write_d(0x00);
	return 0;
}

/* Write a character to the screen with font 8 to current position */
int oled_putchar8(char character, FILE *stream){ // Use ASCII code minus 32, Font8
    if(character == '\n'){
	    oled_pos(oled_current_line_num +1, 8);
		return 0;
    }
	for(uint8_t i = 0; i < 8; ++i){
        oled_write_d(pgm_read_word(&font8[character - 32][i]));
    }
	return 0;
}

/* Set brightness, 0-255 */
void oled_set_brightness(uint8_t lvl){
    oled_write_c(0x81); // Set brightness command
    oled_write_c(lvl); 	// Set brightness level
}

/* Print an arrow at given position*/
void oled_print_arrow(uint8_t row, uint8_t col)
{
	oled_pos(row,col);
	oled_write_d(0b00011000);
	oled_write_d(0b00011000);
	oled_write_d(0b01111110);
	oled_write_d(0b00111100);
	oled_write_d(0b00011000);
}

/* Print a backarrow at given position*/
void oled_print_backarrow(uint8_t row, uint8_t col)
{
    oled_pos(row, col);
    oled_write_d(0b00011000);
    oled_write_d(0b00011000);
    oled_write_d(0b01111110);
    oled_write_d(0b00111100);
    oled_write_d(0b00011000);

}

/* Print Game Over image found in progmem */
void oled_print_game_over()
{
    for(uint8_t i = 0; i < 8; i++){
        oled_pos(i, 0);
        for (uint8_t j=0; j < 128; j++) {
            oled_write_d(pgm_read_word(&game_over_img[i*128 + j]));
        }
    }
}

/* Print the Pong startup image */
void oled_print_pong()
{
    for(uint8_t i = 0; i < 8; i++){
        oled_pos(i, 0);
        for (uint8_t j=0; j < 128; j++) {
            oled_write_d(pgm_read_word(&pong_img[i*128 + j]));
        }
    }
}




// Menu
// - Start new game 
// - See/reset 
// - highscore
// - Calibrate joystick 
// - Set difficulty 
// - Debugging 


//////////////////////////////////////////////////////////////////////////

//void test(){
	//const char FlashString[] PROGMEM = "This is a string held completely in flash memory.";
	//// -> LCD_puts(PSTR("Program Memory String"));
//}
//
//static unsigned int LCD_SegTable[] PROGMEM =
//{
    //0xEAA8,     // '*'
    //0x2A80,     // '+'
    //0x4000,     // ','
    //0x0A00,     // '-'
    //0x0A51,     // '.' Degree sign
    //0x4008,     // '/'
//}
