/*
 * systick.c
 *
 *  Created on: Oct 12, 2024
 *      Author: tcbir
 */

#include "systick.h"
#include "stm32f4xx.h"

// millisecond delay
#define SYSTICK_LOAD_VAL		(16000)
#define CTRL_ENABLE 			(1U<<0)
#define CTRL_CLKSRC 			(1U<<2)
#define CRTL_COUNTFLAG			(1U<<16)


void systick_delay_Ms(int n){

	SysTick->VAL = 0U;
	SysTick->LOAD = SYSTICK_LOAD_VAL;
	SysTick->CTRL |= CTRL_CLKSRC | CTRL_ENABLE;

	for(int i = 0; i < n; i ++){
		while((SysTick->CTRL & CRTL_COUNTFLAG) == 0){}
	}

	SysTick->CTRL = 0U;
}
