/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for the AVR ADC driver
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/


#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*
 * Description :
 * Select the way VREF is selected for ADC
 * 1.AREF : VREF is entered throw and external AREF PIN in micro-controller.
 * 2.AVCC : VREF is the same as AVCC (5v analog).
 * 3.INTERNAL : VREF is 2.56v from internal micro-controller circuit.
 */
typedef  enum{
	AREF,AVCC,INTERNAL =3
}ADC_ReferenceVolatge;

/*
 * Description :
 * Select ADC clock by defining the Pre-scaler F_ADC=F_CPU/Pre-scaler.
 */
typedef enum{
	FCPU_2 =1 ,FCPU_4 ,FCPU_8 ,FCPU_16 ,FCPU_32 ,FCPU_64 ,FCPU_128
}ADC_Prescaler;

/*
 * Description :
 * Structure passed to ADC_init function as parameter
 * containing reference voltage & Pre-scaler for ADC.
 */
typedef struct{
	ADC_ReferenceVolatge ref_volt;
	 ADC_Prescaler prescaler;
	}ADC_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
*******************************************************************************/

/*
* Description :
* Function to initialize the ADC driver that takes pointer to ADC_ConfigType
* the User can change the ADC_ConfigType.
*/
void ADC_init(const ADC_ConfigType *Config_Ptr);

/*
 * Description :
 * Function to read the analog data from a certain ADC channel by polling
 * and returns the digital data after conversion.
 */
uint16 ADC_readChannel(uint8 ch_num);


#endif /* ADC_H_ */
