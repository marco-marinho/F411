//
// Created by marco on 3/27/2022.
//

#ifndef F411_SYSTICK_H
#define F411_SYSTICK_H

#include <stdint.h>
#define SYSTICK_LOAD_VAL 16000

void systick_enable(uint32_t ticks);
void systick_delay_ms(uint32_t delay);

#endif //F411_SYSTICK_H
