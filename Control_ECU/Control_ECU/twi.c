/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: twi.c
 *
 * Description: Source file for the AVR I2C driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#include <avr/io.h>
#include "twi.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Init-ialize the TWI device with configuration from structure
 */
void TWI_init(const TWI_ConfigType * Config_Ptr){

	/* Bit Rate:from user
	 * Set pre-scaler =1 (TWPS=00 and F_CPU=8Mhz) */
	TWBR = Config_Ptr ->bit_rate ;
	TWSR = 0x00;
	TWAR = 0xFE & Config_Ptr-> address;  /* my address as slave */
	TWCR = (1 << TWEN) ;     /* enable TWI*/
}

/*
 * Description :
 * Function responsible for Enable TWI & send start bit
 */
void TWI_start(void){
	/*
	 * TWSTA=1 to send the start bit
	 * TWINT=1 to clear the TWINT flag before sending the start bit
	 * TWEN=1 to enable TWI Module by polling
	 * then wait until the start bit send successfully (TWINT flag = 1)
	 */
	TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN)  ;

     while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*
 * Description :
 * Function responsible to send stop bit
 */
void TWI_stop(void){
	/*
	 * TWSTO=1 to send the stop bit
	 * TWINT=1 to clear the TWINT flag before sending the stop bit
	 * TWEN=1 to enable TWI Module by polling
	 */
	TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN)  ;
}

/*
 * Description :
 * Function responsible to send data
 */
void TWI_writeByte(uint8 data){
/*
 * put data in TWDR Reg
 * TWINT=1 to clear the TWINT flag before sending the data
 * TWEN=1 to enable TWI Module by polling
 * then wait until the data send successfully (TWINT flag = 1)
 */
	TWDR = data;
	TWCR = (1 << TWEN) |  (1 << TWINT);
    while(BIT_IS_CLEAR(TWCR,TWINT));

}

/*
 * Description :
 * Function responsible to receive ACK from slave after sending data
 */
uint8 TWI_readByteWithACK(void){
	/*
	 * TWEA=1 to send the ACK
	 * TWINT=1 to clear the TWINT flag before reading the data
	 * TWEN=1 to enable TWI Module by polling
	 * then wait until the start bit send successfully (TWINT flag = 1)
	 * then read the data
	 */
	TWCR = (1 << TWEA) | (1 << TWINT) | (1 << TWEN)  ;

	while(BIT_IS_CLEAR(TWCR,TWINT));

	return TWDR;
}

/*
 * Description :
 * Function responsible to receive NACK from slave after sending data
 */
uint8 TWI_readByteWithNACK(void){
	/*
	 * TWINT=1 to clear the TWINT flag before reading the data
	 * TWEN=1 to enable TWI Module by polling
	 * then wait until the start bit send successfully (TWINT flag = 1)
	 * then read the data
	 */
	TWCR = (1 << TWINT) | (1 << TWEN)  ;

	while(BIT_IS_CLEAR(TWCR,TWINT));

	return TWDR;
}

/*
 * Description :
 * Function responsible to get status bits
 */
uint8 TWI_getStatus(void){

	uint8 status;
	 /*
	  * get TWS3:7 without first 3 bits in TWSR reg.
	  * then read the status
	  */
	status = TWSR & 0xF8;
	return status;
}


