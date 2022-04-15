//
// Created by marco on 4/14/22.
//

#ifndef F411_EXTI_H
#define F411_EXTI_H

#include <stdbool.h>

typedef enum EXTI_NR{
    EXTI0 = 0,
    EXTI1 = 1,
    EXTI2 = 2,
    EXTI3 = 3,
    EXTI4 = 4,
    EXTI5 = 5,
    EXTI6 = 6,
    EXTI7 = 7,
    EXTI8 = 8,
    EXTI9 = 9,
    EXTI10 = 10,
    EXTI11 = 11,
    EXTI12 = 12,
    EXTI13 = 13,
    EXTI14 = 14,
    EXTI15 = 15,
}EXTI_NR_Typedef;

typedef struct exti_callback{
    void (*exti[16])();
}exti_callback_t;

void exti_set_callback(EXTI_NR_Typedef exti, void (*callback)());

void EXTI15_10_IRQHandler(void);

void exti_set_global_irq(bool status);

int8_t sysconfig_set_clk_en(bool status);

int8_t exti_set_port(GPIO_TypeDef* gpio, EXTI_NR_Typedef exti);

int8_t exti_set_mask(EXTI_NR_Typedef exti, bool state);

int8_t exti_set_falling_trigger(EXTI_NR_Typedef exti, bool state);

int8_t exti_set_NVIC(EXTI_NR_Typedef exti, bool state);

int8_t exti_gpio_en(GPIO_TypeDef* gpio, EXTI_NR_Typedef exti);

#endif //F411_EXTI_H
