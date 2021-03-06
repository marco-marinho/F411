//
// Created by marco on 3/27/2022.
//

#ifndef F411_GPIO_H
#define F411_GPIO_H
#include "stm32f4xx.h"

typedef enum GPIO_MODE{
    OUTPUT,
    INPUT,
    ALTERNATE,
    ANALOG,
}GPIO_MODE;

typedef enum GPIO_ENUM{
    GPIOA_ENUM,
    GPIOB_ENUM,
    GPIOC_ENUM,
    GPIOD_ENUM,
    GPIOE_ENUM,
    GPIOH_ENUM,
}GPIO_ENUM;

void gpio_pin_set_mode(GPIO_TypeDef *gpio, uint8_t pin, GPIO_MODE mode);

void gpio_pin_set_AF_mode(GPIO_TypeDef *gpio, uint8_t pin, uint8_t mode);

void AHB1_gpio_enable(GPIO_TypeDef *gpio);

int8_t GPIO_as_enum(GPIO_TypeDef *gpio);
#endif //F411_GPIO_H
