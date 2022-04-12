//
// Created by marco on 3/27/2022.
//

#ifndef F411_ADC_H
#define F411_ADC_H

#include "stm32f4xx.h"

void adc_init(void);

void adc_start_conversion(void);
void adc_set_continous(void);
uint32_t adc_read(void);
void adc_set_sequence(const uint8_t* channels, uint8_t num_channels);

#endif //F411_ADC_H
