
#include <stdio.h>
#include "uart.h"
#include <stdint.h>
#include "systick.h"

int main(){

	uart2_rxtx_init();

	while(1){
		systick_delay_Ms(1000);
		printf("test\n\r");
	}
}

