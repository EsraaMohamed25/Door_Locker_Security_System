/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: twi.c
 *
 * Description: Header file for the AVR I2C driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef uint32 TWI_BaudRate;
typedef uint32 TWI_Address;

typedef struct{
 TWI_Address address;
 TWI_BaudRate bit_rate;
}TWI_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Init-ialize the TWI device with configuration from structure
 */
void TWI_init(const TWI_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for Enable TWI & send start bit
 */
void TWI_start(void);

/*
 * Description :
 * Function responsible to send stop bit
 */
void TWI_stop(void);

/*
 * Description :
 * Function responsible to send data
 */
void TWI_writeByte(uint8 data);

/*
 * Description :
 * Function responsible to receive ACK from slave after sending data
 */
uint8 TWI_readByteWithACK(void);

/*
 * Description :
 * Function responsible to receive NACK from slave after sending data
 */
uint8 TWI_readByteWithNACK(void);

/*
 * Description :
 * Function responsible to get status bits
 */
uint8 TWI_getStatus(void);


#endif /* TWI_H_ */
