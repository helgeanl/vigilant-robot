//
//  menu.c
//  Byggern
//
//  Created by Helge-André Langåker on 18.09.15.
//  Copyright (c) 2015 Helge-André Langåker. All rights reserved.
//

#include "menu.h"
#include "driv_OLED.h"

/************************************************************************/
/*                      Private variables                               */
/************************************************************************/  
static uint8_t current_arrow_position;
static uint8_t previous_arrow_position;
static menu_t * g_menu;

/************************************************************************/
/*                      Private functions                                */
/************************************************************************/
void node_destroy(menu_t * node){
	uint8_t i;
	for(i = 0; i < 6; i++){
		if(node->next[i] != NULL){
			menu_node_destroy(node->next[i]);
		}
	}
	free(node);
}


/************************************************************************/
/*                      Public functions                                */
/************************************************************************/
void menu_set_arrow_position(uint8_t pos){
	if(pos != 0 && pos <= 7 ){
        previous_arrow_position = current_arrow_position;
		current_arrow_position = pos;
	}
}

uint8_t menu_get_arrow_position(){
	return current_arrow_position;
}

void menu_print_arrow(){
    oled_pos(previous_arrow_position, 0);
    fprintf(FONT8, " ");                        // Clear previous arrow
	oled_print_arrow(current_arrow_position,0); // Print new arrow
}

void menu_print(){
	oled_reset();                                   // Clear screen
	oled_pos(0,0);
	fprintf(FONT8,"%s\n", g_menu->line[0]);         // Print header
    for(int i=1; i <= g_menu->num_choices; i++){
        fprintf(FONT5,"%s\n", g_menu->line[i]);     // Print menu lines
    }
}

// Initialize menu with headers and choices for sub-menus
void menu_init(){
    current_arrow_position = 1;                 // Initialize arrow position to line 1
    previous_arrow_position = 1;
    
    // Main menu
    g_menu = malloc(sizeof(menu_t));
    g_menu->index = 0;
	g_menu->num_choices = 5;
    g_menu->back = NULL;							// Pointer to parent node = NULL
    g_menu->line[0] = "Main Menu";					// Header for top node
    g_menu->line[1] = "Start new game";				// Menu line 1
    g_menu->line[2] = "See Pong";					// Menu line 2
    g_menu->line[3] = "Highscore";					// Menu line 3
    g_menu->line[4] = "Calibrate";					// Menu line 4
    g_menu->line[5] = "Preferences";				// Menu line 5
    g_menu->line[6] = "";							// Menu line 6
    g_menu->line[7] = "";							// Menu line 7
    
	
    //Sub-menu 0 - Start new game
    g_menu->next[0] = malloc(sizeof(menu_t));		// Allocate memory for child node 0
    g_menu->next[0]->back = g_menu;					// Pointer to parent node
    g_menu->next[0]->index = 1;
    g_menu->next[0]->num_choices = 2;
    g_menu->next[0]->line[0] = "New Game";			// Header for child node 0
    g_menu->next[0]->line[1] = "Joystick";
    g_menu->next[0]->line[2] = "Playstation";

	//Sub-sub-menu 5 - New Game - Joystick
	g_menu->next[0]->next[0] = malloc(sizeof(menu_t));
	g_menu->next[0]->next[0]->back = g_menu->next[0];
	g_menu->next[0]->next[0]->line[0] = "Score: ";
	g_menu->next[0]->next[0]->num_choices = 0;
	g_menu->next[0]->next[0]->index = 2;
	
	//Sub-sub-menu 5 - New Game - Playstation
	g_menu->next[0]->next[1] = malloc(sizeof(menu_t));
	g_menu->next[0]->next[1]->back = g_menu->next[0];
	g_menu->next[0]->next[1]->line[0] = "Score: ";
	g_menu->next[0]->next[1]->num_choices = 0;
	g_menu->next[0]->next[1]->index = 3;
    
    //Sub-menu 1 - See/reset, not used
    g_menu->next[1] = NULL;

    //Sub-menu 2 - Highscore, not used
    g_menu->next[2] = NULL;
	
    //Sub-menu 3 - Calibrate joystick
    g_menu->next[3] = malloc(sizeof(menu_t));
    g_menu->next[3]->back = g_menu;
    g_menu->next[3]->line[0] = "Calibrate";
    g_menu->next[3]->num_choices = 0;
	g_menu->next[3]->index = 4;
	
    //Sub-menu 5 - Preferences
    g_menu->next[4] = malloc(sizeof(menu_t));
    g_menu->next[4]->back = g_menu;
    g_menu->next[4]->line[0] = "Preferences";
    g_menu->next[4]->line[1] = "Debug Mode";
    g_menu->next[4]->line[2] = "Melody";
	g_menu->next[4]->num_choices = 2;
	g_menu->next[4]->index = 5; 
    
	//Sub-sub-menu 5 - Debug
	g_menu->next[4]->next[0] = malloc(sizeof(menu_t));
	g_menu->next[4]->next[0]->back = g_menu->next[4];
	g_menu->next[4]->next[0]->line[0] = "Debug Mode";
	g_menu->next[4]->next[0]->line[1] = "Encoder value";
	g_menu->next[4]->next[0]->num_choices = 1;
	g_menu->next[4]->next[0]->index = 6;
    
	//Sub-sub-menu 5 - Melody
	g_menu->next[4]->next[1] = malloc(sizeof(menu_t));
	g_menu->next[4]->next[1]->back = g_menu->next[4];
	g_menu->next[4]->next[1]->line[0] = "Melody";
	g_menu->next[4]->next[1]->line[1] = "Mario";
	g_menu->next[4]->next[1]->line[2] = "Underworld";
	g_menu->next[4]->next[1]->line[3] = "Imperial March";
	g_menu->next[4]->next[1]->line[4] = "Sorcerer's App";
	g_menu->next[4]->next[1]->line[5] = "Fuer Elise";
	g_menu->next[4]->next[1]->line[6] = "Startup sound";
	g_menu->next[4]->next[1]->num_choices = 6;
	g_menu->next[4]->next[1]->index = 7;
    
}


uint8_t menu_home(){
	if(g_menu->back == NULL){
		return 0;
	}
    while(g_menu->back != NULL){
        g_menu = g_menu->back;
    }
    menu_print(g_menu);
    menu_set_arrow_position(1);
    menu_print_arrow();
	return 1;
}

uint8_t menu_back(){
    if(g_menu->back != NULL){
        g_menu = g_menu->back;
        menu_print();
        menu_set_arrow_position(1);
        menu_print_arrow();
		return 1;
    }
	return 0;
}

uint8_t menu_next(){
    if(g_menu->next[menu_get_arrow_position() -1] != NULL){
        g_menu = g_menu->next[menu_get_arrow_position() -1];
        menu_print();
        menu_set_arrow_position(1);
        if(g_menu->num_choices > 0){
            menu_print_arrow();
        }
		return 1;
    }
	return 0;
}

uint8_t menu_get_index(){
    return g_menu->index;
    
}

uint8_t menu_get_choices(){
    return g_menu->num_choices;
}

void menu_destroy(){
    menu_home();
    menu_node_destroy(g_menu);
}



