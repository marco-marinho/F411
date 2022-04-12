#include <stdio.h>
#include "usart2.h"

#define PRINTF_CHAR_LIMIT (256U)

static uint16_t compute_uart_div(const uint32_t PeriphClk, const uint32_t Baudrate){
    return (PeriphClk + (Baudrate / 2U)) / Baudrate;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, const uint32_t PeriphClk, const uint32_t Baudrate){
    USARTx->BRR = compute_uart_div(PeriphClk, Baudrate);
}

void usart2_tx_init(void){

    // Enable GPIOA
    RCC->AHB1ENR |= GPIOAEN;

    // Set GPIOA2 to alternate function
    GPIOA->MODER &= ~(1U<<4);
    GPIOA->MODER |= (1U<<5);

    // Set alternate function type to AF07
    GPIOA->AFR[0] &= ~(0x0F<<8);
    GPIOA->AFR[0] |= (0x07<<8);

    //Enable APB1
    RCC->APB1ENR |= USART2EN;

    //Set baudrate
    uart_set_baudrate(USART2, SYS_CLK, UART_BAUDRATE);

    //Enable Tx
    USART2->CR1 |= CR1_TE;

    //Enable UART
    USART2->CR1 |= CR1_UE;
}

void usart2_rx_init(void){

    // Enable GPIOA
    RCC->AHB1ENR |= GPIOAEN;

    // Set GPIOA3 to alternate function
    GPIOA->MODER &= ~(1U<<6);
    GPIOA->MODER |= (1U<<7);

    // Set alternate function type to AF07
    GPIOA->AFR[0] &= ~(0x0F<<12);
    GPIOA->AFR[0] |= (0x07<<12);

    //Enable APB1
    RCC->APB1ENR |= USART2EN;

    //Set baudrate
    uart_set_baudrate(USART2, SYS_CLK, UART_BAUDRATE);

    //Enable Rx
    USART2->CR1 |= CR1_RE;

    //Enable UART
    USART2->CR1 |= CR1_UE;
}

void usart2_write(char ch){

    while(!(USART2->SR & SR_TXE)){
    }

    USART2->DR = ch;
}

char usart2_read(void){
    while(!(USART2->SR & SR_RXNE)){
    }
    return USART2->DR;
}

void usart2_printf(const char* str){
    int total = 0;
    while(*str != '\0'){
        if(total++ > PRINTF_CHAR_LIMIT){
            break;
        }
        usart2_write(*str++);
    }
}