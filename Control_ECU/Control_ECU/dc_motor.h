/******************************************************************************
 *
 * Module: DC_Motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the AVR DC Motor driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
#include"gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_PORT                       PORTB_ID

#define DC_MOTOR_PIN_IN1                    PIN0_ID
#define DC_MOTOR_PIN_IN2                    PIN1_ID
#define DC_MOTOR_PIN_IN3
#define DC_MOTOR_PIN_IN4

#define DC_MOTOR_PIN_EN1                    PIN3_ID
#define DC_MOTOR_PIN_EN2

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*
 * Description :
 *Select the direction of the movement of the motor.
 */
typedef  enum{
	stop,CW,A_CW
}DcMotor_State;

/*******************************************************************************
 *                              Functions Prototypes                           *
*******************************************************************************/

/*
* Description :
*Function to initialize the DC Motor driver
*Setup the direction for the two motor pins through the GPIO driver.
*Stop at the DC-Motor at the beginning through the GPIO driver.
*/
void DcMotor_Init(void);

/*
* Description :
*The function responsible for rotate the DC Motor CW or A-CW or
*stop the motor based on the state input state value.
*Send the required duty cycle to the PWM driver based on the
*required speed value.
*/
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DC_MOTOR_H_ */
