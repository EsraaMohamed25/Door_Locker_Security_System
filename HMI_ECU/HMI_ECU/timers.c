/******************************************************************************
 *
 * Module: Timers
 *
 * File Name: timers.c
 *
 * Description: Source file for the AVR Timer1 driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#include <avr/io.h>
#include "timers.h"
#include<avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/* Call the Call Back function In case of OVER mood */

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/*
 * In case of COMPARE mood
 */

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the Timer driver.
 */

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{

	TCCR1A = (1 << FOC1A) | ((TCCR1A & 0xFC) | (Config_Ptr->mode & 0x03));
	TCCR1B = ((TCCR1B & 0xF8) | (Config_Ptr->prescaler & 0x07)) | ((TCCR1B & 0xE7) | ((Config_Ptr->mode & 0x0C)<<1));
	 /* Set timer initial value from user */
	TCNT1 = Config_Ptr->initial_value;
	if(Config_Ptr->mode == CTC)
	{
		OCR1A = Config_Ptr->compare_value;
	}
	TIMSK |= (1<<OCIE1A) ;

}
/*
 * Description:
 * Function to disable the Timer1.
 */
void Timer1_deInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
}
/*
 * Description:
 *Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;

}




