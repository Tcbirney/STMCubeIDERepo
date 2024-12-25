
#include <stdio.h>
#include <stdint.h>
#include "tim.h"
#include "stm32f4xx.h"


#define GPIOA_EN 	(1U<<0)

// used for setting mode
#define PIN10 		(1U<<10)
#define PIN11 		(1U<<11)

// defines alternate mode
#define PIN20 		(1U<<20)
#define PIN21 		(1U<<21)
#define PIN22 		(1U<<22)
#define PIN23 		(1U<<23)


int main(){

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



	tim2_output_compare();

	while(1){}
}

