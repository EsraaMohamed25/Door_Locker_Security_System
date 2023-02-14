/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the AVR UART driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#include <avr/io.h>
#include "uart.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for Init-ialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * UART_Config_Ptr){

	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = parity bit from user
	 * USBS    = num. of stop bits from user
	 * UCSZ1:0 = num. of data bits from user
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL);
	UCSRC = (UCSRC & 0xCF)|((UART_Config_Ptr->parity)<< 4);
	UCSRC = (UCSRC & 0xF7)|((UART_Config_Ptr->stop_bit)<< 3);
	UCSRC = (UCSRC & 0xF9)|((UART_Config_Ptr->data_bits)<< 1);

	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / ((UART_Config_Ptr->baud_rate) * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;

}

/*
 * Description :
 * Function responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data){
	/*
	 * wait until UDRE flag is set which means Tx buffer (UDR) is empty
	 * and be ready for transimitting a new byte
	 * then write the data in Tx buffer (UDR) so UDRE is clear
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE));
	UDR = data;
}

/*
 * Description :
 * Function responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void){
	/*
	 * wait until RXC flag is set which means UART receive data and ready to read it
	 * then read the received data from Rx buffer (UDR) so UDRE is clear
	 */
	while(BIT_IS_CLEAR(UCSRA,RXC));
	return UDR;

}

/*
 * Description :
 * Function responsible for send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str){

	uint8 i=0;
	/* send the whole string */
	while ( Str[i] != '\0'){
		UART_sendByte(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Function responsible for receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str){

	uint8 i=0;
	Str[i]= UART_recieveByte();  /* receive the first byte */

	/* receive the whole string until the '#' */
	while ( Str[i] != '#'){
		i++;
		Str[i]= UART_recieveByte();
	}

	/* after receiving the string and '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
