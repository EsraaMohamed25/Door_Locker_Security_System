/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: header file for the buzzer driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include"gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID         PORTA_ID
#define BUZZER_PIN_ID         PIN0_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * function to setup direction for the buzzer as output
 * Turn off the buzzer at the beginning
 */
void Buzzer_init(void);
/*
 * Description :
 * function to enable buzzer
 */
void Buzzer_on(void);
/*
 * Description :
 * function to disable buzzer
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
