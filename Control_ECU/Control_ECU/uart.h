/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Header file for the AVR UART driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
/*
 * enum to define Number of Bit Data
 */
typedef enum{
	Data_5_Bits, Data_6_Bits, Data_7_Bits, Data_8_Bits ,Data_9_Bits =7
}UART_BitData;

/*
 * enum to Enable Parity Bit(EVEN, ODD)/ Disable Parity Bit
 */
typedef enum{
	Parity_Disable, Parity_Enable_Even = 2, Parity_Enable_Odd
}UART_Parity;

/*
 * enum to define Number of Stop Bits
 */
typedef enum{
	Stop_1_Bit, Stop_2_Bit
}UART_StopBit;

/*
 * variable to define Baud Rate
 */
typedef uint32 UART_BaudRate ;


/*
 * Structure to Config. UART Parameters:
 * - Number of Bit Data
 * - Baud Rate
 * - Number of Stop Bits
 * - Parity Enable/Disable
 */
typedef struct{
	UART_BitData data_bits;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;


/*******************************************************************************
 *                              Functions Prototypes                           *
*******************************************************************************/

/*
 * Description :
 * Function responsible for Init-ialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * UART_Config_Ptr);

/*
 * Description :
 * Function responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Function responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Function responsible for send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Function responsible for receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str);

#endif /* UART_H_ */
