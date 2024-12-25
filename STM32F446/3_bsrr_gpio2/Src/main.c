#include "stm32f4xx.h"


#define GPIOAEN			(1UL<<0)
#define PIN5			(1UL<<5)
#define LED_PIN			PIN5

int main(){


	// enable ahb1 clock signal
	RCC->AHB1ENR |= GPIOAEN;

	// set direction for PORTA pin 5
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= (~(1U << 11));

	while(1){
		GPIOA->BSRR = LED_PIN;
		for(int i = 0; i < 200000; i ++){}

		GPIOA->BSRR = (1U<<21);
		for(int i = 0; i < 200000; i ++){}
	}

}
