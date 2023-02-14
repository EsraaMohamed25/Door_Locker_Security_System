/******************************************************************************
 *
 * Description: Main file for the Door Locker Security Systems (Human Machine Interface)
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#include <avr/interrupt.h>
#include "HMI_ECU.h"
#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include "timers.h"
#include <util/delay.h>

/*******************************************************************************
 *                                Global Variables                             *
 *******************************************************************************/

static uint8 state;
static volatile uint8 counter;

/*******************************************************************************
 *                                Main Function                                *
 *******************************************************************************/
/*
 * Description:
 * Function to count number of overflows
 */
void timer1(void){
	counter++;
}

int main(void)
{
	LCD_init();

	/* Enable global interrupts in MC by setting the I-Bit */
	SREG  |= (1<<7);

	UART_ConfigType UART_Config ={Data_8_Bits ,Parity_Disable ,Stop_1_Bit ,9600 };
	UART_init( &UART_Config );

	Timer1_ConfigType Timer1_Config ={ 0,1000 ,F_CPU_1024,CTC};
	Timer1_setCallBack(timer1);

	UART_sendByte(READY);

	for(;;){

		state= UART_recieveByte();

		switch(state){

		case ENTER_PASS:

			/* Wait until Control-ECU is ready to receive */
			while(UART_recieveByte() != READY);
			LCD_clearScreen();
			LCD_displayString("Plz Enter Pass:");
			LCD_moveCursor(1,0);
			HMI_ECU_takePass();
				break;

		case RE_ENTER_PASS:

			/* Wait until Control-ECU is ready to receive */
			while(UART_recieveByte() != READY);
			LCD_clearScreen();
			LCD_displayString("Plz Re-enter the");
			LCD_moveCursor(1,0);
			LCD_displayString("same Pass: ");
			HMI_ECU_takePass();
			break;

		case MAIN_OPTIONS:
			LCD_clearScreen();
			LCD_displayString("Right Pass");
			_delay_ms(1000);
			LCD_clearScreen();
			LCD_displayString("+ : Open Door");
			LCD_displayStringRowColumn(1,0,"- : Change Pass");
			/* get & send the pressed button from USER */
			while(UART_recieveByte() != READY);
			UART_sendByte( KEYPAD_getPressedKey() );
			break;

		case OPEN_DOOR:
			LCD_clearScreen();
			LCD_displayString("Door is Unlocking");
			//delay 15 sec
			Timer1_init(&Timer1_Config);
			while(counter < 15);
			Timer1_deInit();
			counter =0;
			LCD_clearScreen();

			break;

		case CLOSE_DOOR:
			LCD_clearScreen();
			LCD_displayString("Door is locking");
			//delay 15 sec
			Timer1_init(&Timer1_Config);
			while(counter < 15);
			Timer1_deInit();
			counter =0;
			LCD_clearScreen();
			break;

		case BUZZER_ON:
			LCD_clearScreen();
			LCD_displayString("ERROR !!");
			//delay 1 min
			Timer1_init(&Timer1_Config);
			while(counter < 60);
			Timer1_deInit();
			counter =0;
			LCD_clearScreen();
			break;
		}
	}
}


