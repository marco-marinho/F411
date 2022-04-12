//
// Created by marco on 3/26/2022.
//

#ifndef F411_USART2_H
#define F411_USART2_H

#include <stdint.h>
#include "stm32f4xx.h"


#define SYS_CLK (16000000)
#define UART_BAUDRATE 115200
#define CR1_TE (1U<<3)
#define CR1_UE (1U<<13)
#define CR1_RE (1U<<2)
#define SR_TXE (1U<<7)
#define SR_RXNE (1U<<5)
#define GPIOAEN (1U << 0)
#define USART2EN (1U << 17)

void usart2_tx_init(void);

void usart2_write(char ch);

char usart2_read(void);

void usart2_printf(const char* str);

#endif //F411_USART2_H
