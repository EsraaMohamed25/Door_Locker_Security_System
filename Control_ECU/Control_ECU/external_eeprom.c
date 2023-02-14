/******************************************************************************
 *
 * Module: EEPROM
 *
 * File Name: eeprom.c
 *
 * Description: Source file for the AVR EEPROM driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#include "external_eeprom.h"
#include "twi.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for send address of memory to write data in it
 */
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data){
	/*
	 * Send the Start Bit
	 * then check if send successfully or no
	 */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	/*
	 * Send the required memory location address
	 * then check if send successfully or no
	 */
	TWI_writeByte((uint8)(u16addr));
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/*
	 * write byte to eeprom
	 * then check if send successfully or no
	 */
	TWI_writeByte(u8data);
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* Send the Stop Bit */
	TWI_stop();

	return SUCCESS;
}

/*
 * Description :
 * Function responsible for send address of memory to read data from it
 */
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data){
	/*
	 * Send the Start Bit
	 * then check if send successfully or no
	 */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	/*
	 * Send the required memory location address
	 * then check if send successfully or no
	 */
	TWI_writeByte((uint8)(u16addr));
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;
	/*
	 * Send the repeated Start Bit
	 * then check if send successfully or no
	 */
	TWI_start();
	if (TWI_getStatus() != TWI_REP_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=1 (read) */
	TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)| 1));
	if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
		return ERROR;
	/*
	 * read byte from memory
	 * then check if send successfully or no
	 */
	*u8data = TWI_readByteWithNACK();
	if (TWI_getStatus() != TWI_MR_DATA_NACK)
		return ERROR;

	/* Send the Stop Bit */
	TWI_stop();

	return SUCCESS;
}
