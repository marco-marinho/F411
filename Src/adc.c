//
// Created by marco on 3/27/2022.
//

#include "adc.h"

void adc_init(void){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    ADC1->CR2 |= ADC_CR2_ADON;
}

void adc_set_continous(void){
    ADC1->CR2 |= ADC_CR2_CONT;
}

void adc_start_conversion(void){
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void){
    while(!(ADC1->SR & ADC_SR_EOC)){
    }
    return ADC1->DR;
}

void adc_set_sequence(const uint8_t* channels, uint8_t num_channels){
    ADC1->SQR3;
    for(int cur_chan = 0; cur_chan < num_channels; cur_chan++){
        if(cur_chan < 6){
            ADC1->SQR3 &= ~(0x1F << cur_chan * 5);
            ADC1->SQR3 |= (channels[cur_chan] << cur_chan * 5);
        }
        else if(cur_chan < 12){
            ADC1->SQR2 &= ~(0x1F << (cur_chan - 6) * 5);
            ADC1->SQR2 |= (channels[cur_chan] << (cur_chan - 6) * 5);
        }
        else{
            ADC1->SQR1 &= ~(0x1F << (cur_chan - 12) * 5);
            ADC1->SQR1 |= (channels[cur_chan] << (cur_chan - 12) * 5);
        }
    }
    ADC1->SQR1 &= ~(0xF << 20);
    ADC1->SQR1 |= ((num_channels - 1) << 20);
}