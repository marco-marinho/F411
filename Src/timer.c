//
// Created by marco on 3/27/2022.
//

#include "timer.h"

void timer_clock_enable(TIM_TypeDef *tim){
    if(tim == TIM1) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    }
    else if(tim == TIM2) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    }
    else if(tim == TIM3) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    }
    else if(tim == TIM4) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    }
    else if(tim == TIM5) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
    }
    else if(tim == TIM9) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
    }
    else if(tim == TIM10) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
    }
    else if(tim == TIM11) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
    }
}

void timer_enable(TIM_TypeDef *tim){
    tim->CR1 |= TIM_CR1_CEN;
}

void timer_set_prescaler(TIM_TypeDef *tim, uint32_t value){
    tim->PSC = value - 1;
}

uint32_t timer_get_prescaler(TIM_TypeDef *tim){
    return tim->PSC;
}

void timer_set_autoreload(TIM_TypeDef *tim, uint32_t value){
    tim->ARR = value - 1;
}

void timer_clear(TIM_TypeDef *tim){
    tim->CNT = 0;
}

void timer_wait_for_uif(TIM_TypeDef *tim){
    while(!(tim->SR & TIM_SR_UIF)){}
    tim->SR &= ~TIM_SR_UIF;
}

void timer_set_oc_toggle(TIM_TypeDef *tim, uint8_t channel){
    switch(channel){
        case 1:
        {
            tim->CCMR1 &=~ (0x07<<TIM_CCMR1_OC1M_Pos);
            tim->CCMR1 |= (0x03<<TIM_CCMR1_OC1M_Pos);
            return;
        }
        case 2:
        {
            tim->CCMR1 &=~ (0x07<<TIM_CCMR1_OC2M_Pos);
            tim->CCMR1 |= (0x03<<TIM_CCMR1_OC2M_Pos);
            return;
        }
        case 3:
        {
            tim->CCMR2 &=~ (0x07<<TIM_CCMR2_OC3M_Pos);
            tim->CCMR2 |= (0x03<<TIM_CCMR2_OC3M_Pos);
            return;
        }
        case 4:
        {
            tim->CCMR2 &=~ (0x07<<TIM_CCMR2_OC4M_Pos);
            tim->CCMR2 |= (0x03<<TIM_CCMR2_OC4M_Pos);
            return;
        }
        default:
            return;
    }
}

void timer_set_cc_mode(TIM_TypeDef *tim, uint8_t channel, uint8_t mode){
    // Clear CC1S and set mode. If mode is illegal, return without taking action.
    if(mode > 3){
        return;
    }
    switch(channel){
        case 1:
        {
            tim->CCMR1 &=~ (0x03<<TIM_CCMR1_CC1S_Pos);
            tim->CCMR1 |= (mode<<TIM_CCMR1_CC1S_Pos);
            return;
        }
        case 2:
        {
            tim->CCMR1 &=~ (0x03<<TIM_CCMR1_CC2S_Pos);
            tim->CCMR1 |= (mode<<TIM_CCMR1_CC2S_Pos);
            return;
        }
        case 3:
        {
            tim->CCMR2 &=~ (0x03<<TIM_CCMR2_CC3S_Pos);
            tim->CCMR2 |= (mode<<TIM_CCMR2_CC3S_Pos);
            return;
        }
        case 4:
        {
            tim->CCMR2 &=~ (0x03<<TIM_CCMR2_CC4S_Pos);
            tim->CCMR2 |= (mode<<TIM_CCMR2_CC4S_Pos);
            return;
        }
        default:
            return;
    }
}

void timer_enable_channel(TIM_TypeDef *tim, uint8_t channel){
    switch(channel){
        case 1:
        {
            tim->CCER |= TIM_CCER_CC1E;
            return;
        }
        case 2:
        {
            tim->CCER |= TIM_CCER_CC2E;
            return;
        }
        case 3:
        {
            tim->CCER |= TIM_CCER_CC3E;
            return;
        }
        case 4:
        {
            tim->CCER |= TIM_CCER_CC4E;
            return;
        }
        default:
            return;
    }
}

uint8_t timer_get_if(TIM_TypeDef *tim, uint8_t channel){
    switch(channel){
        case 1:
        {
            return (tim->SR & TIM_SR_CC1IF_Msk)!=0;
        }
        case 2:
        {
            return (tim->SR & TIM_SR_CC2IF_Msk)!=0;
        }
        case 3:
        {
            return (tim->SR & TIM_SR_CC3IF_Msk)!=0;
        }
        case 4:
        {
            return (tim->SR & TIM_SR_CC4IF_Msk)!=0;;
        }
        default:
            return 0;
    }
}

void timer_set_polarity(TIM_TypeDef *tim, uint8_t channel, uint8_t mode){
    if(mode > 3 || mode == 2){
        return;
    }
    switch(channel){
        case 1:
        {
            tim->CCER &=~(0x01 << TIM_CCER_CC1P_Pos);
            tim->CCER &=~(0x01 << TIM_CCER_CC1NP_Pos);
            tim->CCER |= (mode & 0x01 << TIM_CCER_CC1P_Pos);
            tim->CCER |= (((mode & 0x02) >> 1) << TIM_CCER_CC1NP_Pos);
            return;
        }
        case 2:
        {
            tim->CCER &=~(0x01 << TIM_CCER_CC2P_Pos);
            tim->CCER &=~(0x01 << TIM_CCER_CC2NP_Pos);
            tim->CCER |= (mode & 0x01 << TIM_CCER_CC2P_Pos);
            tim->CCER |= (((mode & 0x02) >> 1) << TIM_CCER_CC2NP_Pos);
            return;
        }
        case 3:
        {
            tim->CCER &=~(0x01 << TIM_CCER_CC3P_Pos);
            tim->CCER &=~(0x01 << TIM_CCER_CC3NP_Pos);
            tim->CCER |= (mode & 0x01 << TIM_CCER_CC3P_Pos);
            tim->CCER |= (((mode & 0x02) >> 1) << TIM_CCER_CC3NP_Pos);
            return;
        }
        case 4:
        {
            tim->CCER &=~(0x01 << TIM_CCER_CC4P_Pos);
            tim->CCER &=~(0x01 << TIM_CCER_CC4NP_Pos);
            tim->CCER |= (mode & 0x01 << TIM_CCER_CC4P_Pos);
            tim->CCER |= (((mode & 0x02) >> 1) << TIM_CCER_CC4NP_Pos);
            return;
        }
        default:
            return;
    }
}