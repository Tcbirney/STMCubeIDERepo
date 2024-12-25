
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include <stdint.h>

uint32_t adc_val;

float voltage_to_temp(float voltage);
float convert_adc_to_voltage(uint32_t adc_val);


int main(){

	uart2_rxtx_init();
	init_temp_sensor();


	while(1){
		start_conversion();
		adc_val = adc_read();
		printf("test2: %ld \n\r", adc_val);
	}
}

