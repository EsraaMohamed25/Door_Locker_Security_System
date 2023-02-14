/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the buzzer driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/
#include "buzzer.h"
#include "gpio.h"


/*
 * Description :
 * function to setup direction for the buzzer as output
 * Turn off the buzzer at the beginning
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 * function to enable buzzer
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID, LOGIC_HIGH);

}
/*
 * Description :
 * function to disable buzzer
 */
void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID, LOGIC_LOW);

}
