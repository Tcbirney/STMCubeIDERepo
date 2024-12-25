
#include <stdio.h>
#include <stdint.h>
#include "tim.h"
#include "stm32f4xx.h"




int main(){

	tim3_pa5_input_capture();
	tim3_pa6_input_capture();

	while(1){}
}

