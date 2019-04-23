#include "rcc.h"

void RCC_init(void) {
    RCC->CR |= RCC_CR_HSEON;    // HSE ON // 12 MHz
    while (!(RCC->CR & RCC_CR_HSERDY_Msk)); 
    
}