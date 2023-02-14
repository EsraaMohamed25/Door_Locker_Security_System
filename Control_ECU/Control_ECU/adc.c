/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the AVR ADC driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#include "adc.h"
#include "common_macros.h"
#include <avr/io.h>

/*
* Description :
* Function to initialize the ADC driver that takes pointer to ADC_ConfigType
* the User can change the ADC_ConfigType.
*/
void ADC_init(const ADC_ConfigType *Config_Ptr){

	/* ADMUX Register Bits Description:
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX =0;
	ADMUX = (ADMUX & 0x3F)|((Config_Ptr->ref_volt)<<6);
	/* ADCSRA Register Bits Description:
	 * ADEN   = 1 Enable ADC
	 * ADIE  = 0 Disable INT
	 * ADPS2:0 = 011 to choose Pre-scaler= 8 (ADC_Clock=1Mhz/8=125Khz)
	 *  ADC must operate in range 50-200Khz
	 */
	ADCSRA =(1<<ADEN);
	ADCSRA =(ADCSRA & 0xF8) | (Config_Ptr->prescaler);
}

/*
 * Description :
 * Function to read the analog data from a certain ADC channel by polling
 * and returns the digital data after conversion.
 */
uint16 ADC_readChannel(uint8 ch_num){
	ADMUX = (ADMUX &0xE0) | (ch_num & 0x07); /* Set the channel from User */
	SET_BIT(ADCSRA ,ADSC);    /* Start conversion */
	while(BIT_IS_CLEAR(ADCSRA ,ADIF));  /* Wait until ADIF flag is set to 1 by polling */
	SET_BIT(ADCSRA,ADIF);   /* clear ADIF flag */
	return ADC;
}

