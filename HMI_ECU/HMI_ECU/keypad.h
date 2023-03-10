 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the AVR KEYPAD driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* defined for board */
/* #define STANDARD_KEYPAD */

/* definitions for keypad */
#define KEYPAD_NUM_ROWS 	  4
#define KEYPAD_NUM_COLS		  4

/* Keypad rows Configurations */
#define KEYPAD_PORT_ID		    PORTC_ID
#define KEYPAD_FIRST_ROW_PIN_ID		PIN0_ID

/* Keypad columns Configurations */
//#define KEYPAD_COL_PORT_ID			PORTC_ID
#define KEYPAD_FIRST_COL_PIN_ID		PIN4_ID

/* Configure Buttons of Keypad */
#define KEYPAD_BUTTON_PRESSED	LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED	LOGIC_HIGH

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Get the value of pressed key
 */
uint8 KEYPAD_getPressedKey(void);
/*
 * Block keypad
 */
void KEYPAD_stop ();

#endif /* KEYPAD_H_ */
