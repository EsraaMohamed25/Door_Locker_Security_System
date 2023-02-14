/******************************************************************************
 *
 * Module: DC_Motor
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the AVR DC Motor driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#include <avr/io.h>
#include "dc_motor.h"
#include "common_macros.h"
#include "gpio.h"
#include "pwm.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
* Description :
*Function to initialize the DC Motor driver
*Setup the direction for the two motor pins through the GPIO driver.
*Stop at the DC-Motor at the beginning through the GPIO driver.
*/
void DcMotor_Init(void){
	/* Set motor pins as output pins*/
	GPIO_setupPinDirection(DC_MOTOR_PORT,DC_MOTOR_PIN_IN1,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT,DC_MOTOR_PIN_IN2,PIN_OUTPUT);

	/* Initially, Stop the motor */
	GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_IN1,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_IN2,LOGIC_LOW);

}

/*
* Description :
*The function responsible for rotate the DC Motor CW or A-CW or
*stop the motor based on the state input state value.
*Send the required duty cycle to the PWM driver based on the
*required speed value.
*/
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	/* Set the direction of movement of DC-Motor according to state CW/ACW/STOP */
	if(state == CW){
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_IN1,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_IN2,LOGIC_LOW);
	}else if( state == A_CW){
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_IN1,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_IN2,LOGIC_HIGH);
	}else if(state == stop){
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_IN1,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_IN2,LOGIC_LOW);
	}
//	DC_MOTOR_PORT = (DC_MOTOR_PORT & 0xFC) |(state & 0x03);
	/* Set DC-Motor speed using PWM */
	PWM_Timer0_Start(speed);
}
