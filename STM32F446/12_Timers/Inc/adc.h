/*
 * adc.h
 *
 *  Created on: Oct 12, 2024
 *      Author: tcbir
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void init_temp_sensor();
void start_conversion();
uint32_t adc_read();

#endif /* ADC_H_ */
