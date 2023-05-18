/*
 * acd.h
 *
 *  Created on: Mar 21, 2023
 *      Author: elsabado
 */

#ifndef ADC_H_
#define ADC_H_
#include <inc/tm4c123gh6pm.h>



void adc_init (void);


//------------ADC0_InSeq3------------

// Busy-wait analog to digital conversion

// Input: none

// Output: 12-bit result of ADC conversion
int adc_read (void);



#endif /* ADC_H_ */
