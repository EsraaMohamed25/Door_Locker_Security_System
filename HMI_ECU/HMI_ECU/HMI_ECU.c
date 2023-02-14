/******************************************************************************
 *
 * Description: Source file for the Door Locker Security Systems (Human Machine Interface)
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#include "HMI_ECU.h"
#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include <util/delay.h>

static volatile uint8 key;
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* Function to :
 * Take the password from user
 * Send the pass to Control_ECU by UART
 * Display * on the screen
 */
void HMI_ECU_takePass(void){
	uint8 i;
	for(i=0;i <5 ;i++){

		/* get & send the pressed button from keypad */
		key = KEYPAD_getPressedKey();
		/* Check if the user finish entering the pass or no */
		if( key >=0 && key <=9){
			UART_sendByte(key);
			/*Display * for each char of pass */
			LCD_displayCharacter('*');
//			LCD_intgerToString(key);
		}
		else
			i--;
		/* Press time */
		_delay_ms(500);
	}
	return;
}
