/*
 * adc.c
 *
 *  Created on: Oct 12, 2024
 *      Author: tcbir
 */

#include "stm32f4xx.h"
#include "adc.h"



// for ENABling ADC to have clock signal
#define ADC1_EN			(1U<<8)

// settting seq len
#define ADC1_SQ_LEN_1 	(0x00)

// for turning on the temp sensor and
// turning off the battery sensor
#define CCR_TSVREFE 	(1U<<25)
#define CCR_VBATE 		(1U<<24)

// actually turning on the adc
#define CR2_ADON		(1U<<0)
#define CR2_SWSTART 	(1U<<30)

// end of conversion flag to check that data is ready
#define SR_EOC 			(1U<<1)



void init_temp_sensor(){

	// adc1 is on the APB2 bus, so enable the clock signal for it
	RCC->APB2ENR |= ADC1_EN;


	// set 0d18 into the first 5 bits of the sqr3 register
	// to point it to the temperature sensor
	ADC1->SQR3 |= (1U << 4);
	ADC1->SQR3 &= ~(1U << 3);
	ADC1->SQR3 &= ~(1U << 2);
	ADC1->SQR3 |= (1U << 1);
	ADC1->SQR3 &= ~(1U << 0);

	// set the sequence length to only require 1 conversion
	ADC1->SQR1 = ADC1_SQ_LEN_1;

	// turn on temp sensor and turn off vbat sensor
	ADC->CCR |= CCR_TSVREFE;
	ADC->CCR &= ~CCR_VBATE;

	// turn on the adc
	ADC1->CR2 |= CR2_ADON;

}


void start_conversion(){
	ADC1->CR2 |= CR2_SWSTART;
}


uint32_t adc_read(){

	// wait until the conversion  is finished
	while((ADC1->SR & SR_EOC)==0){}

	return ADC1->DR;

}














