/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#include "gpio.h"
#include "lcd.h"
#include "common_macros.h"
#include <util/delay.h>
#include <stdlib.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Send Command to the LCD.
 */

void LCD_sendCommand(uint8 command){

	GPIO_writePin(LCD_RW_PORT,LCD_RW_PIN,LOGIC_LOW);  //Clear RW =0
	GPIO_writePin(LCD_RS_PORT,LCD_RS_PIN,LOGIC_LOW);  //Clear RS =0
	_delay_ms(1);        //delay for processing Tas = 50ns
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_HIGH);  //Set enable =1
	_delay_ms(1);       //delay for processing Tpw - Tdws = 190ns

#if(LCD_DATA_BITS_MODE == 8)

	GPIO_writePort(LCD_DATA_PORT,command);    //out the command to the data bus

#elif(LCD_DATA_BITS_MODE == 4)
	/* out the required command to the data bus 4-bits*/
	GPIO_writePin(LCD_DATA_PORT,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB7_PIN_ID,GET_BIT(command,7));

	_delay_ms(1);    // delay for processing processing Tdsw = 100ns
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_LOW); // Clear enable =0
	_delay_ms(1);   // delay for processing Th = 13ns
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_HIGH);  // Set enable =1
	_delay_ms(1);    // delay for processing Tpw - Tdws = 190ns

/* in data sheet we should send the 4 last bits at first then the first 4bits*/
	GPIO_writePin(LCD_DATA_PORT,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB7_PIN_ID,GET_BIT(command,3));

#endif
	_delay_ms(1);      // delay for processing Tdsw = 100ns
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_LOW); // Clear enable =0
	_delay_ms(1);     // delay for processing Th = 13ns

}

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode (4/8 -bits).
 */

void LCD_init(void){
	/*Set RS and E pins as output pins */
	GPIO_setupPinDirection(LCD_RS_PORT,LCD_RS_PIN,PIN_OUTPUT);   //RS as OUT
	GPIO_setupPinDirection(LCD_E_PORT,LCD_E_PIN ,PIN_OUTPUT);   //E as OUT
	GPIO_setupPinDirection(LCD_RW_PORT,LCD_RW_PIN,PIN_OUTPUT);   //RS as OUT

	_delay_ms(20);      //LCD Power ON delay always > 15ms

#if(LCD_DATA_BITS_MODE == 8)

	GPIO_setupPortDirection(LCD_DATA_PORT,PORT_OUTPUT);   //Data_Bus as OUT

	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);   //Setup the LCD Data Mode 8-bits.

#elif(LCD_DATA_BITS_MODE == 4)
	/* Set Data_Bus as Output*/
	GPIO_setupPinDirection(LCD_DATA_PORT ,LCD_DB4_PIN_ID ,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT ,LCD_DB5_PIN_ID ,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT ,LCD_DB6_PIN_ID ,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT ,LCD_DB7_PIN_ID ,PIN_OUTPUT);

	/* Send these commands to activate 4-bits mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/*Setup the LCD Data Mode 4-bits */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#endif
	LCD_sendCommand(LCD_CURSOR_OFF);   //cursor off
	LCD_sendCommand(LCD_CLEAR_COMMAND);   //clear screen =0 at the begin
}

/*
 * Description :
 * Display character from the user on the screen.
 */

void LCD_displayCharacter(uint8 character){

	GPIO_writePin(LCD_RW_PORT,LCD_RW_PIN,LOGIC_LOW);  // Set RW =0 to write
	GPIO_writePin(LCD_RS_PORT,LCD_RS_PIN,LOGIC_HIGH);  // Set RS =1
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_HIGH);  // Set enable =1
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 8)

	GPIO_writePort(LCD_DATA_PORT,character);    //out the command to the data bus

#elif(LCD_DATA_BITS_MODE == 4)
	/* out the required command to the data bus 4-bits*/
	GPIO_writePin(LCD_DATA_PORT,LCD_DB4_PIN_ID,GET_BIT(character,4));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB5_PIN_ID,GET_BIT(character,5));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB6_PIN_ID,GET_BIT(character,6));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB7_PIN_ID,GET_BIT(character,7));

	_delay_ms(1);    // delay for  Tdsw = 100ns
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_LOW); // Clear enable =0
	_delay_ms(1);   // delay for Th = 13ns
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_HIGH);  // Set enable =1
	_delay_ms(1);    // delay for Tpw - Tdws = 190ns

/* in data sheet we should send the 4 last bits at first then the first 4bits*/
	GPIO_writePin(LCD_DATA_PORT,LCD_DB4_PIN_ID,GET_BIT(character,0));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB5_PIN_ID,GET_BIT(character,1));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB6_PIN_ID,GET_BIT(character,2));
	GPIO_writePin(LCD_DATA_PORT,LCD_DB7_PIN_ID,GET_BIT(character,3));

#endif

	_delay_ms(1);    // delay for  Tdsw = 100ns
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_LOW); // Clear enable =0
	_delay_ms(1);    // delay for Th = 13ns
}

/*
 * Description :
 * Display string from the user on the screen.
 */

void LCD_displayString(const char *string){
	uint8 i =0;
	while(string[i] != '\0'){
		LCD_displayCharacter(string[i]);
		i++;
	}
}

/*
 * Description :
 * Move the cursor to a specified row and column on the screen.
 */

void LCD_moveCursor(uint8 row,uint8 col){
	uint8 lcd_memory_address;
	switch(row){
	case 0:
		lcd_memory_address= col;
		break;
	case 1:
		lcd_memory_address= col+ 0x40;
		break;
	case 2:
		lcd_memory_address= col+ 0x10;
		break;
	case 3:
		lcd_memory_address= col+ 0x50;
		break;
	}

	LCD_sendCommand(LCD_SET_CURSOR_LOCATION | lcd_memory_address);

}

/*
 * Description :
 * Display the string from user in a specified row and column on the screen.
 */

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *String){

	LCD_moveCursor( row,col );    //go to to the required position on the LCD
	LCD_displayString( String );

}

/*
 * Description :
 * Display the required decimal value on the screen.(convert data to its corresponding ASCII value)
 */

void LCD_intgerToString(int data){
	char array[20];    // array to hold the ASCII result
	itoa(data,array,10);     //Use itoa C function to convert the data to ASCII value, 10 for the base
	LCD_displayString(array);
}

/*
 * Description :
 * Send Clear Command to the screen.
 */

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}
