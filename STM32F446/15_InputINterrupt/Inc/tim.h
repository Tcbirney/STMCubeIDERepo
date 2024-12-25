/*
 * tim.h
 *
 *  Created on: Oct 13, 2024
 *      Author: tcbir
 */

#ifndef TIM_H_
#define TIM_H_


#define SR_UIF			(1U<<0)

void tim2_1hz_init();
void tim2_pa5_output_compare();
void tim3_pa6_input_capture();

#endif /* TIM_H_ */
