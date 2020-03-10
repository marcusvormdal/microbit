#include <stdint.h>

#define __GPIO_BASE_ADDRESS__ 0x50000000
#define __BUTTON_A_PIN__ 17
#define __BUTTON_B_PIN__ 26

#define GPIO ((NRF_GPIO_REGS*)__GPIO_BASE_ADDRESS__)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR; //0x51C
	volatile uint32_t RESERVED1[120]; // 0x520
	volatile uint32_t PIN_CNF[32]; //0x700
} NRF_GPIO_REGS;

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[__BUTTON_A_PIN__] = 0;
	GPIO->PIN_CNF[__BUTTON_B_PIN__] = 0;

	int sleep = 0;
	while(1){
		if(!(GPIO->IN & 1 << __BUTTON_B_PIN__)){
			for(int i = 4; i <= 12; ++i){
				GPIO->OUT &= ~(1<<i);
			}
			for(int i = 13; i <= 15; ++i){
				GPIO->OUT |= (1<<i);
			}
			
		}
	
		if(!(GPIO->IN & 1 << __BUTTON_A_PIN__)){
			for(int i = 4; i <= 12; ++i){
				GPIO->OUT |= (1<<i);
			}
			for(int i = 13; i <= 15; ++i){
				GPIO->OUT &= ~(1<<i);
			}
			
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
