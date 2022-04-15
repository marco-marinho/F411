#include "stm32f411xe.h"

void enable_FPU(void)
{
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));
}