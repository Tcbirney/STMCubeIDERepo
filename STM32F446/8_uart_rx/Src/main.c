
#include <stdio.h>
#include "uart.h"


#define GPIOAEN			(1UL<<0)
#define LED_PIN			(1UL<<5)

char key;


int main(){

	// enable ahb1 clock signal
	RCC->AHB1ENR |= GPIOAEN;

	// set direction for PORTA pin 5
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= (~(1U << 11));

	uart2_rxtx_init();

	while(1){
		key = uart2_read();
		if(key == 'y'){
			GPIOA->BSRR = LED_PIN;
		}
		if(key == 'n'){
			GPIOA->BSRR = (1U<<21);
		}

	}



}
