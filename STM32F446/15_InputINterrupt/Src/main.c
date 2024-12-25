
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "exti.h"
#include "uart.h"

#define GPIOA_EN 			(1U<<0)

int main(){

	// enable clock to GPIOA
	RCC->AHB1ENR |= GPIOA_EN;

	// set alternate mode for pin5
	GPIOA->MODER |= (1U<<10);

	pc13_exti_init();
	uart2_rxtx_init();

	while(1){}
}



static void exti_callback(){

	GPIOA->ODR ^= (1U<<5);
	printf("button_pushed\n\r");

}

void EXTI15_10_IRQHandler(){

	if(EXTI->PR & LINE13){
		// clear the PR flag so that we can
		// tell if its been triggered again
		// weird but the flag is cleared by setting it to 1
		EXTI->PR |= LINE13;
		exti_callback();
	}

}
