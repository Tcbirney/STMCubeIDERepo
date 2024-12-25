/*
 * uart.h
 *
 *  Created on: Oct 11, 2024
 *      Author: tcbir
 */

#ifndef UART_H_
#define UART_H_


#include "stm32f4xx.h"
#include <stdint.h>

#define SYS_FREQ 		16000000
#define BAUDRATE		115200
#define GPIOAEN			(1UL<<0)
#define UART2EN			(1UL<<17)
#define CR1_TE			(1U<<3)
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)


void uart2_init();


#endif /* UART_H_ */
