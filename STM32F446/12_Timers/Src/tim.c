/*
 * tim.c
 *
 *  Created on: Oct 13, 2024
 *      Author: tcbir
 */


#include "stm32f4xx.h"
#include "tim.h"

#define APB1_TIM2_EN			(1U<<0)
#define CR1_TIM2_EN				(1U<<0)

void tim2_1hz_init(){

	// enable apb1 for tim2
	RCC->APB1ENR |= APB1_TIM2_EN;

	// set the prescaler value
	// clock is 16MHz so 16,000,000/1600 = 10,000 to count to
	TIM2->PSC = 1600-1;

	//set the autoreload val
	TIM2->ARR = 10000-1;

	//clear the current counter val
	TIM2->CNT = 0;

	// enable counter
	TIM2->CR1 |= CR1_TIM2_EN;

}










