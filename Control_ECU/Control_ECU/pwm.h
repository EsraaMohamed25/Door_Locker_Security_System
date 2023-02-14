/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for the PWM driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
* Description :
* Function to initialize the PWM driver that takes duty cycle of the clock
* the User can change the duty_cycle which change PWM_Config.
*/
void PWM_Timer0_Start(uint8 duty_cycle);



#endif /* PWM_H_ */
