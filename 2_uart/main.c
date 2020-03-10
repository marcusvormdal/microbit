#include <stdint.h>
#include "gpio.h"
#include "uart.h"
#include <stdio.h>

#define BUTTON_A_PIN 17
#define BUTTON_B_PIN 26

int toggleLigths(int current_val){
    if(current_val){
        for(int i = 4; i <= 12; ++i){
            GPIO->OUT |= (1<<i);
        }
        for(int i = 13; i <= 15; ++i){
            GPIO->OUT &= ~(1<<i);
        }
        return 0;
    }
    else{
        for(int i = 4; i <= 12; ++i){
            GPIO->OUT &= ~(1<<i);
        }
        for(int i = 13; i <= 15; ++i){
            GPIO->OUT |= (1<<i);
        }
        return 1;
    }
}


ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
    uart_send(*letter);
    letter++;
    }
    return count;
}

ssize_t _read(int fd, void *buf, size_t count){
    char *str = (char *)(buf);
    char letter;
    do {
        letter = uart_read();
    } while(letter == '\0');
    *str = letter;
    return 1;
}

int main(){
	

    uart_init();
    int lights_on = 0;
    // Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[BUTTON_A_PIN] = 0;
	GPIO->PIN_CNF[BUTTON_B_PIN] = 0;

	int sleep = 0;

	while(1){
		if(!(GPIO->IN & 1 << BUTTON_B_PIN)){
            uart_send('B');
		}
	
		if(!(GPIO->IN & 1 << BUTTON_A_PIN)){
            iprintf("Write two integers: \n\r\a");
            int a = 0;
            int b = 0;
            scanf("%d",&a);
            iprintf("%d\n\r",a);
            scanf("%d",&b);
            iprintf("%d\n\r\a",b);

            int c = a*b;
            iprintf("Your result was: %d\n\r",c);


		}

        if(uart_read() != '\0'){
            lights_on = toggleLigths(lights_on);
            iprintf("The chemical formula for Ketamine is C%dH%dClNO\n\r", 13, 16);

        }
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}