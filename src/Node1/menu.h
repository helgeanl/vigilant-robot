//
//  menu.h
//  Byggern
//
//  Created by Helge-André Langåker on 18.09.15.
//  Copyright (c) 2015 Helge-André Langåker. All rights reserved.
//

#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdlib.h>

/**
 The menu system is built up as a node tree with the main menu as top node. 
 Each node has pointers to both parent node and children.
 */
typedef struct menu {
    char *line[8];          // Number of lines of text in menu
    uint8_t index;          // Index of node
	uint8_t num_choices;    // Number of children nodes
	
    struct menu *next[6];   // List of pointers to children nodes
    struct menu *back;      // Pointer to parent node
} menu_t;


/**
 Initialize main menu and sub menus with headers and sub menu choices
 */
void    menu_init();

/**
 Prints out menu on screen
 */
void    menu_print();

/**
 Set current arrow positon
 @param pos, Current arrow position
 */
void    menu_set_arrow_position(uint8_t pos);

/**
 Get current arrow position
 @return position
 */
uint8_t menu_get_arrow_position();

/**
 Print arrow on current arrow position and clears previous arrow
 */
void    menu_print_arrow();

/**
 Go to home menu
 @return 
 */
uint8_t menu_home();

/**
 Go one step back
 @return 1 if done, 0 if at home menu
 */
uint8_t menu_back();

/**
 Go to sub menu
 @return 1 if available, 0 i not
 */
uint8_t menu_next();

/**
 Get index of current menu
 @return index 
 */
uint8_t menu_get_index();

/**
 Get number of choices of current menu
 @return choices 
 */
uint8_t menu_get_choices();

/**
 Destroy menu system and free allocated memory 
 */
void menu_destroy();


/* -- Example of use: --
 menu_init();                    // Initialize node tree (menu system)
 menu_print();                   // Print current menu to screen
 menu_print_arrow();             // Print arrow for menu selection
 */


#endif /* MENU_H_ */
