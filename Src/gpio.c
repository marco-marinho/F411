//
// Created by marco on 3/27/2022.
//

#include "gpio.h"

void gpio_pin_set_mode(GPIO_TypeDef *gpio, uint8_t pin, GPIO_MODE mode){
    switch(mode){
        case OUTPUT:
            gpio->MODER |= (1U<< (pin*2));
            gpio->MODER &= ~(1U<<(pin*2 + 1));
            break;
        case INPUT:
            gpio->MODER &= ~(1U<<(pin*2));
            gpio->MODER &= ~(1U<<(pin*2 + 1));
            break;
        case ALTERNATE:
            gpio->MODER &= ~(1U<<(pin*2));
            gpio->MODER |= (1U<<(pin*2 + 1));
            break;
        case ANALOG:
            gpio->MODER |= (1U<< (pin*2));
            gpio->MODER |= (1U<<(pin*2 + 1));
            break;
        default:
            break;
    }
}

void gpio_pin_set_AF_mode(GPIO_TypeDef *gpio, uint8_t pin, uint8_t mode){
    if( pin < 8) {
        gpio->AFR[0] &= ~(0xF0 << (pin * 4));
        gpio->AFR[0] |= (mode << (pin * 4));
    }
    else{
        pin = pin - 8;
        gpio->AFR[1] &= ~(0xF0 << (pin * 4));
        gpio->AFR[1] |= (0xF0 << (pin * 4));
    }
}

void AHB1_gpio_enable(GPIO_TypeDef *gpio){
    if(gpio == GPIOA){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    }
    else if(gpio == GPIOB){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    }
    else if(gpio == GPIOC){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    }
    else if(gpio == GPIOD){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    }
    else if(gpio == GPIOE){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    }
}


