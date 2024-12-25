/*
 * tim.c
 *
 *  Created on: Oct 13, 2024
 *      Author: tcbir
 */


#include "stm32f4xx.h"
#include "tim.h"

// enables clock signals to each of the clocks
#define APB1_TIM2_EN			(1U<<0)
#define APB1_TIM3_EN			(1U<<1)

// in each timer there is a cr1 reg and they enable each timer
#define CR1_CEN					(1U<<0)

// capture output mode for timer 2
#define CCMR_OCM1_TOGGLE		(1U<<5)|(1U<<4)
#define CCMR_CC1S_INPUT			(1U<<0)

// enable the channel 1 capture compare register for each timer
#define CCER_CC1_EN				(1U<<0)



// enable clock for gpioa in rcc
#define GPIOA_EN 	(1U<<0)

// used for setting mode for pin 5
#define PIN10 		(1U<<10)
#define PIN11 		(1U<<11)

// defines alternate mode for pin 5
#define PIN20 		(1U<<20)
#define PIN21 		(1U<<21)
#define PIN22 		(1U<<22)
#define PIN23 		(1U<<23)


// used for setting mode for pin 6
#define PIN12 		(1U<<12)
#define PIN13 		(1U<<13)

// defines alternate mode for pin 6
#define PIN24 		(1U<<24)
#define PIN25 		(1U<<25)
#define PIN26 		(1U<<26)
#define PIN27 		(1U<<27)



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
	TIM2->CR1 |= CR1_CEN;

}


void tim2_pa5_output_compare(){


	// enable clock to GPIOA
	RCC->AHB1ENR |= GPIOA_EN;

	// set alternate mode for pin5
	GPIOA->MODER &= ~PIN10;
	GPIOA->MODER |= PIN11;

	// set which alternate function to use
	// af1 for being tied to the
	GPIOA->AFR[0] |= PIN20;
	GPIOA->AFR[0] &= ~PIN21;
	GPIOA->AFR[0] &= ~PIN22;
	GPIOA->AFR[0] &= ~PIN23;



	// enable apb1 for tim2
	RCC->APB1ENR |= APB1_TIM2_EN;

	// set the prescaler value
	// clock is 16MHz so 16,000,000/1600 = 10,000 to count to
	TIM2->PSC = 1600-1;

	//set the autoreload val
	TIM2->ARR = 10000-1;

	// set the mode for the Output of the compare
	TIM2->CCMR1 |= CCMR_OCM1_TOGGLE;

	//enable the output signal for the compare flag
	TIM2->CCER |= CCER_CC1_EN;


	//clear the current counter val
	TIM2->CNT = 0;

	// enable counter
	TIM2->CR1 |= CR1_CEN;

}



void tim3_pa6_input_capture(){

	// enable clock to GPIOA
	RCC->AHB1ENR |= GPIOA_EN;

	// set alternate mode for pin6
	GPIOA->MODER &= ~PIN12;
	GPIOA->MODER |= PIN13;


	// set which alternate function to use af2 for PA6
	GPIOA->AFR[0] &= ~PIN24;
	GPIOA->AFR[0] |=  PIN25;
	GPIOA->AFR[0] &= ~PIN26;
	GPIOA->AFR[0] &= ~PIN27;


	// enable apb1 for tim2
	RCC->APB1ENR |= APB1_TIM3_EN;

	// set the prescaler value
	// clock is 16MHz so 16,000,000/1600 = 10,000 to count to
	TIM3->PSC = 1600-1;

	// set the mode to input capture for ch1
	TIM3->CCMR1 |= CCMR_CC1S_INPUT;

	//enable the channel to be able to receive input
	TIM3->CCER |= CCER_CC1_EN;

	// enable counter
	TIM3->CR1 |= CR1_CEN;

}
