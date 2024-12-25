
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOA_EN 			(1U<<0)


static void usart2_callback();

char key = 'a';


int main(){

	// enable clock to GPIOA
	RCC->AHB1ENR |= GPIOA_EN;

	// set alternate mode for pin5
	GPIOA->MODER |= (1U<<10);


	uart2_rxtx_interrupt_init();

	while(1){}
}



static void usart2_callback(){

	key = USART2->DR;

	GPIOA->ODR ^= (1U<<5);

}

void USART2_IRQHandler(){

	if(USART2->SR & SR_RXNE){
		usart2_callback();
	}

}
