#include <stdlib.h>

#include "stm32f4xx.h"
#include "usart2.h"
#include "adc.h"
#include "gpio.h"
#include "systick.h"
#include "timer.h"
#include "itm.h"
#include "exti.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

void print_irq_13(void){
    usart2_printf("IRQ13\r\n");
}

int main(void)
{

    usart2_tx_init();
    exti_gpio_en(GPIOC, EXTI13);

    exti_set_callback(EXTI13, print_irq_13);

    systick_enable(SYSTICK_LOAD_VAL);

	while(1){
        if(!(GPIOC->IDR & 1<<13)){
            usart2_printf("Button\r\n");
            systick_delay_ms(1000);
        }
        else {
            usart2_printf("Idle\r\n");
            systick_delay_ms(1000);
        }
    }
}
#pragma clang diagnostic pop
