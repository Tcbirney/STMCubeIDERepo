// we want to turn on an led
// there is an led  and a push button on the nucleo board


// where is the led connected
// what is the port and pin of the led
// need to look in nucleo documentation


// port: A
// pin: 5


// mem map tells us this
#define PERIPH_BASE 			(0x40000000UL)

// table 10 tells us these
#define AHB1_PERIPH_OFFSET 		(0x00020000UL)
#define AHB1_PERIPH_BASE		(PERIPH_BASE + AHB1_PERIPH_OFFSET)



// addr for port a
#define GPIOA_OFFSET			(0x00000000UL)
#define GPIOA_BASE				(AHB1_PERIPH_BASE + GPIOA_OFFSET)

// mode register determines pin mode
#define MODE_R_OFFSET			(0x0UL)
#define GPIOA_MODE_R			(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

// data output register
#define OD_R_OFFSET				(0x14UL)
#define GPIOA_OD_R				(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

// led is pin 5 of port a
#define PIN5					(1U<<5)
#define LED_PIN					PIN5



// for rcc, enabling ahb1
#define RCC_OFFSET 				(0x3800UL)
#define RCC_BASE				(AHB1_PERIPH_BASE + RCC_OFFSET)

// addr for enabling ahb1
#define RCC_AHB1EN_OFFSET 		(0x30UL)
#define RCC_AHB1EN_R			(*(volatile unsigned int *)(RCC_BASE + RCC_AHB1EN_OFFSET))

#define GPIOAEN 				(1U<<0) // create 32b word with 1 at idx 0


int main(){

	//	Enable clock access to GPIO port a
	RCC_AHB1EN_R |= GPIOAEN;

	// Set PA5 as output, set bit 10 = 1 and 11 = 0
	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &= (~(1U<<11));

	while(1){
		// Inside the infinite loop, toggle
		GPIOA_OD_R ^= LED_PIN;
		for(int i = 0; i < 100000; i++){}
	}

}










