//
// Created by marco on 3/27/2022.
//

#ifndef F411_TIMMER_H
#define F411_TIMMER_H

#include "stm32f4xx.h"

void timer_clock_enable(TIM_TypeDef *tim);

void timer_enable(TIM_TypeDef *tim);

void timer_set_prescaler(TIM_TypeDef *tim, uint32_t value);

void timer_set_autoreload(TIM_TypeDef *tim, uint32_t value);

void timer_clear(TIM_TypeDef *tim);

void timer_wait_for_uif(TIM_TypeDef *tim);

void timer_set_oc_toggle(TIM_TypeDef *tim, uint8_t channel);

void timer_set_cc_mode(TIM_TypeDef *tim, uint8_t channel, uint8_t mode);

void timer_enable_channel(TIM_TypeDef *tim, uint8_t channel);

void timer_set_polarity(TIM_TypeDef *tim, uint8_t channel, uint8_t mode);

uint8_t timer_get_if(TIM_TypeDef *tim, uint8_t channel);

uint32_t timer_get_prescaler(TIM_TypeDef *tim);

#endif //F411_TIMMER_H
