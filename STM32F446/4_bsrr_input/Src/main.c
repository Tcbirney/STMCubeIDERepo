#include "stm32f4xx.h"


#define GPIOAEN			(1UL<<0)
#define GPIOCEN			(1UL<<2)

#define PIN5			(1UL<<5)
#define PIN13			(1UL<<13)

#define LED_PIN			PIN5
#define BTN_PIN 		PIN13

int main(){


	// enable ahb1 clock signal
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	// set direction for PORTA pin 5
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= (~(1U << 11));


	// set direction for PORTA pin 13
	GPIOC->MODER &= (~(1U << 27));
	GPIOC->MODER &= (~(1U << 26));


	while(1){
//
//		if(GPIOC->IDR & BTN_PIN){
//			GPIOA->BSRR = LED_PIN;
//		}
//		else{
//			GPIOA->BSRR = (1U<<21);
//		}
	}
}
