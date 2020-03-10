
#include <stdint.h>
#include "gpio.h"


#define UART ((NRF_UART_REG*)0x40002000)



typedef struct {

    volatile uint32_t STARTRX;
    volatile uint32_t STOPRRX;
    volatile uint32_t STARTTX;
    volatile uint32_t STOPTX;
    volatile uint32_t RESERVED0[3];
    volatile uint32_t SUSPEND;
    volatile uint32_t RESERVED1[56];

    volatile uint32_t CTS;
    volatile uint32_t NCTS;
    volatile uint32_t RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t TXDRDY;
    volatile uint32_t RESERVED3;
    volatile uint32_t ERROR;
    volatile uint32_t RESERVED4[7];
    volatile uint32_t RXTO;
    volatile uint32_t RESERVED5[110];

    volatile uint32_t INTEN;
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED6[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED7[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED8;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED9;
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED10[17];
    volatile uint32_t CONFIG;
} NRF_UART_REG;



#define TGT_RXD 25
#define TGT_TXD 24



void uart_init(){
    	GPIO->DIRSET &= ~(1 << TGT_RXD);

        GPIO->DIRSET |= (1 << TGT_TXD);

        UART->PSELTXD = 24;
        UART->PSELRXD = 25;

        UART->BAUDRATE = 0X00275000;
        UART->PSELCTS = 0XFFFFFFFF;
        UART->PSELRTS = 0XFFFFFFFF;
        UART->ENABLE = 4;
        UART->STARTRX = 1;

}

void uart_send(char letter){
    UART->STARTTX = 1;
    UART->TXDRDY = 0;
    UART->TXD = letter;
    while(!UART->TXDRDY);
    UART->STOPTX = 1;
    
}

char uart_read(){
    UART->STARTRX = 1;
    char temp = UART->RXD;
    if(temp){
        UART->RXDRDY = 0;
        return temp;
    }

    else{
        return('\0');
    }
}
