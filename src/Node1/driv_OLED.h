/*
 * driv_OLED.h
 *
 * Created: 17.09.2015 12:23:50
 *  Author: helgeanl
 */ 


#ifndef DRIV_OLED_H_
#define DRIV_OLED_H_
#include <stdio.h>



void oled_init();
void oled_write_c(uint8_t command);
void oled_write_d(uint8_t data);

void oled_reset();
void oled_clear_line(uint8_t line);
void oled_goto_line(uint8_t line);
void oled_pos(uint8_t row, uint8_t col);
uint8_t oled_get_current_line();

// Use ASCII code minus 32, Font types: FONT8 (8x8), FONT5 (5x7), FONT4 (4x6)
int oled_putchar4(char character, FILE * stream);
int oled_putchar5(char character, FILE* stream);
int oled_putchar8(char character, FILE* stream);

static FILE oled_stream_font4 = FDEV_SETUP_STREAM(oled_putchar4, NULL, _FDEV_SETUP_WRITE);
static FILE oled_stream_font5 = FDEV_SETUP_STREAM(oled_putchar5, NULL, _FDEV_SETUP_WRITE);
static FILE oled_stream_font8 = FDEV_SETUP_STREAM(oled_putchar8, NULL, _FDEV_SETUP_WRITE);

#define FONT4 (&oled_stream_font4)
#define FONT5 (&oled_stream_font5)
#define FONT8 (&oled_stream_font8)

void oled_set_brightness(uint8_t lvl);

void oled_print_arrow(uint8_t row, uint8_t col);
void oled_print_backarrow(uint8_t row, uint8_t col);
void oled_print_game_over();
void oled_print_pong();






#endif /* DRIV_OLED_H_ */