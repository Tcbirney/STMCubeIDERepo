
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

	start_conversion();

	while(1){
		adc_val = adc_read();
		printf("adc_val: %ld \n\r", adc_val);
	}
}

