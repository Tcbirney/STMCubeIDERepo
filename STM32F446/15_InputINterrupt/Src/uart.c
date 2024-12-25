/*
 * uart.c
 *
 *  Created on: Oct 11, 2024
 *      Author: tcbir
 */

#include "uart.h"

int __io_putchar(int ch);
void uart2_write(int ch);
void uart_set_baudrate(uint32_t periph_clock, uint32_t baud_rate);


int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}

void uart2_rxtx_init(){

	// Configure GPIO pins
	// Enable the clock for the tx, rx port pins
	// Enable the UART Peripheral
	RCC->AHB1ENR |= GPIOAEN;


	// PA2 can act as the USART2 tx pin when set to alternate mode
	// PINS 4 and 5 of the MODE Reg for GPIO A control the mode
	// Setting GPIOA->MODER[5:4] = [1, 0] sets PA2 to alternate mode
	GPIOA->MODER &= ~(1UL<<4);
	GPIOA->MODER |= (1UL<<5);

	// pa3 is used as the rx pin for uart2
	GPIOA->MODER &= ~(1UL<<6);
	GPIOA->MODER |= (1UL<<7);

	// The alternate function register determines which alternate function
	// each of the GPIO pins should perform
	// GPIOA->AFR[0][11:8] determines what the alternate function for PA2 is
	// When this range is set to 0111, it sets PA2 to perform the USART2 TX function
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	// the next 4 pits in the register determine the alternate mode for the pa3
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);


	// Configure the UART module

	// enable clock for the USART2 module, which is connected to APB1
	RCC->APB1ENR |= UART2EN;

	// configure baudrate, modifies USART2->BRR
	uart_set_baudrate(SYS_FREQ, BAUDRATE);

	// enable the uart receive and transmit from the USART2 control register
	USART2->CR1 = CR1_TE;
	USART2->CR1 |= CR1_RE;

	// then using the same CR1 enable the uart module itself
	USART2->CR1 |= CR1_UE;

}

char uart2_read(){

	// check if tx register is empty using
	// the TXE pin from the status register
	while((USART2->SR & SR_RXNE) == 0UL){}

	// set the data register with our bit
	return USART2->DR;
}



void uart2_write(int ch){

	// check if tx register is empty using
	// the TXE pin from the status register
	while((USART2->SR & SR_TXE) == 0UL){}

	// set the data register with our bit
	USART2->DR = (ch & 0xFF);
}


void uart_set_baudrate(uint32_t periph_clock, uint32_t baud_rate){
	// lets try this normal one
	// theres a different equation that doesn't
	// make much sense woth the mantissa
	USART2->BRR = (unsigned long)((periph_clock + baud_rate/2U)/baud_rate);
}

