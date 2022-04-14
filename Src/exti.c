//
// Created by marco on 4/14/22.
//

#include <stdbool.h>
#include <stdint.h>
#include "stm32f411xe.h"
#include "gpio.h"
#include "exti.h"

void exti_set_global_irq(bool status){
    if(!status){
        __disable_irq();
    }
    else{
        __enable_irq();
    }
}

void sysconfig_set_clk_en(bool status){
    RCC->APB2ENR &= ~(1 << RCC_APB2ENR_SYSCFGEN_Pos);
    RCC->APB2ENR |= (status << RCC_APB2ENR_SYSCFGEN_Pos);
}

int8_t exti_set_port(GPIO_TypeDef* gpio, EXTI_NR_Typedef exti){
    if(exti>15){
        return -1;
    }
    if(!IS_GPIO_ALL_INSTANCE(gpio)){
        return -2;
    }
    uint8_t bits_to_set;
    switch (GPIO_as_enum(gpio)) {
        case GPIOA_ENUM: {
            bits_to_set = 0;
            break;
        }
        case GPIOB_ENUM: {
            bits_to_set = 1;
            break;
        }
        case GPIOC_ENUM:{
            bits_to_set = 2;
            break;
        }
        case GPIOD_ENUM:{
            bits_to_set = 3;
            break;
        }
        case GPIOE_ENUM:{
            bits_to_set = 4;
            break;
        }
        case GPIOH_ENUM:{
            bits_to_set = 7;
            break;
        }
        default:
            return -3;
    }
    uint8_t exti_cr_nr = exti/4;
    SYSCFG->EXTICR[exti_cr_nr] &= ~(0xf << (exti % 4) * 4);
    SYSCFG->EXTICR[exti_cr_nr] |= ~(bits_to_set << (exti % 4) * 4);
    return 0;
}

int8_t exti_set_mask(EXTI_NR_Typedef exti, bool state){
    if(exti>15){
        return -1;
    }
    if(!state){
        EXTI->IMR &= ~(1U << exti);
    }
    else{
        EXTI->IMR |= (1U << exti);
    }
    return 0;
}

int8_t exti_set_falling_trigger(EXTI_NR_Typedef exti, bool state){
    if(exti>15){
        return -1;
    }
    if(!state){
        EXTI->FTSR &= ~(1U << exti);
    }
    else{
        EXTI->FTSR |= (1U << exti);
    }
    return 0;
}

int8_t exti_set_NVIC(EXTI_NR_Typedef exti, bool state){
    void (*func_to_execute)(IRQn_Type);
    if(!state){
        func_to_execute = &NVIC_DisableIRQ;
    }
    else{
        func_to_execute = &NVIC_EnableIRQ;
    }
    int IRQn;
    switch(exti) {
        case EXTI0:{
            IRQn = EXTI0_IRQn;
            break;
        }
        case EXTI1:{
            IRQn = EXTI1_IRQn;
            break;
        }
        case EXTI2:{
            IRQn = EXTI2_IRQn;
            break;
        }
        case EXTI3:{
            IRQn = EXTI3_IRQn;
            break;
        }
        case EXTI4:{
            IRQn = EXTI4_IRQn;
            break;
        }
        case EXTI5: case EXTI6: case EXTI7: case EXTI8: case EXTI9:
        {
            IRQn = EXTI9_5_IRQn;
            break;
        }
        case EXTI10: case EXTI11: case EXTI12: case EXTI13: case EXTI14: case EXTI15:
        {
            IRQn = EXTI15_10_IRQn;
            break;
        }
        default:
            return -1;
    }
    func_to_execute(IRQn);
}

int8_t exti_gpio_en(GPIO_TypeDef* gpio, EXTI_NR_Typedef exti){
    exti_set_global_irq(false);
    AHB1_gpio_enable(gpio);
    gpio_pin_set_mode(gpio, exti, INPUT);
    sysconfig_set_clk_en(true);
    exti_set_port(gpio, exti);
    exti_set_mask(exti, true);
    exti_set_falling_trigger(exti, true);
    exti_set_NVIC(exti, true);
    exti_set_global_irq(true);
}


