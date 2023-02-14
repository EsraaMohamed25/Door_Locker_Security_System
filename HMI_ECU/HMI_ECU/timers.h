/******************************************************************************
 *
 * Module: Timers
 *
 * File Name: timers.h
 *
 * Description: Header file for the AVR Timer1 driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#ifndef TIMERS_H_
#define TIMERS_H_

#include"std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*
 * enum to choose pre-scaler
 */
typedef enum
{
	No_Clock, F_CPU_CLOCK ,F_CPU_8 , F_CPU_64 , F_CPU_256 , F_CPU_1024
}Timer1_Prescaler;

/*
 * enum to choose mood
 */
typedef enum
{
	NORMAL,CTC =4
}Timer1_Mode;

/*
 * Structure to Config. Timer1 Parameters:
 * - Initial value
 * - Compare value
 * - Pre-scaler
 * - Mode
 */
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
*******************************************************************************/

/*
 * Description:
 * Function to initialize the Timer driver.
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
/*
 * Description:
 * Function to disable the Timer1.
 */
void Timer1_deInit(void);
/*
 * Description:
 *Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMERS_H_ */

