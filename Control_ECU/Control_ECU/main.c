/******************************************************************************
 *
 * Description: Main file for the Door Locker Security Systems (Control ECU)
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#include <avr/io.h>
#include "Control_ECU.h"
#include "uart.h"
#include "external_eeprom.h"
#include "dc_motor.h"
#include "timers.h"
#include "buzzer.h"
#include <avr/interrupt.h>
#include "twi.h"

int main(void){

	Buzzer_init();
	DcMotor_Init();
	/* Enable global interrupts in MC by setting the I-Bit */
	SREG  |= (1<<7);
	UART_ConfigType UART_Config ={Data_8_Bits ,Parity_Disable ,Stop_1_Bit ,9600 };
	UART_init( &UART_Config );

	TWI_ConfigType TWI_Config ={0x01 ,0x02};
	TWI_init( &TWI_Config );

	/* Wait until HMI-ECU is ready to receive */
	while(UART_recieveByte() != READY);
	Control_ECU_createPass();
	for(;;){
		UART_sendByte(MAIN_OPTIONS);
		if(main_options()== '+')
			Control_ECU_openDoor();

		else
			Control_ECU_changePass();
	}
}
