#include <stdlib.h>

#include "stm32f4xx.h"
#include "usart2.h"
#include "adc.h"
#include "gpio.h"
#include "systick.h"
#include "timer.h"
#include "itm.h"

#define GPIOAEN (1U << 0)
#define GPIOCEN (1U << 2)
#define USART2EN (1U << 17)

#define PIN5 (1 << 5U)
#define LED PIN5
#define PIN13 (1 << 13)
#define BUTTON PIN13


void enable_FPU(void)
{
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main(void)
{
//	enable_FPU();
    AHB1_gpio_enable(GPIOA);
    usart2_tx_init();

    // Enable and configure ADC
    gpio_pin_set_mode(GPIOA, 1, ANALOG);

    // LED as timer output
    gpio_pin_set_mode(GPIOA, 5, ALTERNATE);
    gpio_pin_set_AF_mode(GPIOA, 5, 1);

    // PA6 mode alternate function
    gpio_pin_set_mode(GPIOA, 6, ALTERNATE);
    gpio_pin_set_AF_mode(GPIOA, 6, 2);

    adc_init();
    uint8_t seq[] = {1};
    adc_set_sequence(seq, 1);
    adc_set_continous();
    adc_start_conversion();

    // Enable and setup timer 2
    timer_clock_enable(TIM2);
    timer_set_prescaler(TIM2, 1600);
    timer_set_autoreload(TIM2, 10000);
    timer_clear(TIM2);
    timer_enable(TIM2);

    timer_set_oc_toggle(TIM2, 1);
    timer_enable_channel(TIM2, 1);

    // Enable and setup timer 3
    timer_clock_enable(TIM3);
    timer_set_prescaler(TIM3, 16000);
    timer_set_cc_mode(TIM3, 1, 1);
    timer_set_polarity(TIM3, 1, 3);
    timer_enable_channel(TIM3, 1);
    timer_enable(TIM3);

    // Enable systick
    systick_enable(SYSTICK_LOAD_VAL);

    // Enable button
    AHB1_gpio_enable(GPIOC);
    gpio_pin_set_mode(GPIOC, 13, INPUT);

    uint32_t timestamp;
	while(1){
        while(!timer_get_if(TIM3, 1)){}
        timestamp = TIM3->CCR1;
    }
}
#pragma clang diagnostic pop
