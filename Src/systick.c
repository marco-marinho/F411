//
// Created by marco on 3/27/2022.
//

#include "stm32f4xx.h"
#include "systick.h"

void systick_enable(uint32_t ticks){
    SysTick->LOAD = ticks;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
}

void systick_delay_ms(uint32_t delay){
    SysTick->VAL   = 0UL;
    for(uint32_t tick = 0; tick < delay; tick ++){
        while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)){}
    }
}

