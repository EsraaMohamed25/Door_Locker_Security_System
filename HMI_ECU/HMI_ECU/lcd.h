/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Header file for the AVR LCD driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

#define LCD_DATA_BITS_MODE             8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

#define LCD_RS_PORT                PORTA_ID
#define LCD_RS_PIN                  PIN0_ID

#define LCD_RW_PORT                 PORTA_ID
#define LCD_RW_PIN                  PIN1_ID

#define LCD_E_PORT                 PORTA_ID
#define LCD_E_PIN                  PIN2_ID


#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN                 PIN3_ID
#define LCD_DB5_PIN                 PIN4_ID
#define LCD_DB6_PIN                 PIN5_ID
#define LCD_DB7_PIN                 PIN6_ID
#endif

#define LCD_DATA_PORT                  PORTB_ID


/* LCD Prototypes */
void LCD_sendCommand(uint8 command);
void LCD_init(void);
void LCD_displayCharacter(uint8 character);
void LCD_displayString(const char *string);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_intgerToString(int data);
void LCD_clearScreen(void);

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

#endif /* LCD_H_ */
