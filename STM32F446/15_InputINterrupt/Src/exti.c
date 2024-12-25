/*
 * exti.c
 *
 *  Created on: Oct 27, 2024
 *      Author: tcbir
 */


#include "exti.h"


#define GPIOCEN 			(1U<<2)
#define SYSCFGEN			(1U<<14)
#define PORTC_EXTI13		(1U<<5)
#define EXTI13				(1U<<13)

void pc13_exti_init(){

	// disable all interrupts
	__disable_irq();


	// enable gpioc and set pin 13 as input
	RCC->AHB1ENR |= GPIOCEN;
	GPIOC->MODER &= ~(1U<<27);
	GPIOC->MODER &= ~(1U<<26);

	// enable SYSCFG and set pin13 to be sent to the NVIC
	RCC->APB2ENR |= SYSCFGEN;
	SYSCFG->EXTICR[3] |= PORTC_EXTI13;

	// unmask EXTI13
	EXTI->IMR |= EXTI13;

	// select falling edge trigger
	EXTI->FTSR = EXTI13;

	// enable the EXT13 signal
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	// reenable interrupts
	__enable_irq();
}
