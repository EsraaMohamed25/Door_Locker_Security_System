/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#include <avr/io.h>
#include"pwm.h"
#include"gpio.h"

/*
* Description :
* Function to initialize the PWM driver that takes duty cycle of the clock
* the User can change the duty_cycle which change PWM_Config.
*/
void PWM_Timer0_Start(uint8 duty_cycle){
	TCNT0=0;           /* Set timer initial value to 0*/
	/* Set compare value based on the required duty cycle*/
	if(duty_cycle != 100)
		OCR0  = (uint8) ( (duty_cycle * 256) / 100 );
	else
		OCR0 = 255;

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 * */
	TCCR0 |= (1<<WGM00) |(1<<WGM01) | (1<<COM01) | (1<<CS01) ;
	GPIO_setupPinDirection(1,3,PIN_OUTPUT);    /* Set OC0 (PB3) as output pin (where the PWM is generated from MC)*/
}
