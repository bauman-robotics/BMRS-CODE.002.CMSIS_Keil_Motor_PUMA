#include "rcc.h"

void RCC_init(void) {
    RCC->CR |= RCC_CR_HSEON;    // HSE ON // 12 MHz
    while (!(RCC->CR & RCC_CR_HSERDY_Msk)); 
    FLASH->ACR |= 0x02 << FLASH_ACR_LATENCY_Pos;	// Number of wait states
    /***Clear all necessary bits***/
    RCC->CFGR &= ~ RCC_CFGR_PLLMULL;
    RCC->CFGR &= ~ RCC_CFGR_PLLXTPRE;
    RCC->CFGR &= ~ RCC_CFGR_PLLSRC;
    RCC->CFGR &= ~ RCC_CFGR_PPRE1;
    RCC->CFGR &= ~ RCC_CFGR_PPRE2;
    RCC->CFGR &= ~ RCC_CFGR_HPRE;
    RCC->CFGR &= ~ RCC_CFGR_SW; 
    /******/
    RCC->CFGR |= RCC_CFGR_PLLMULL6;// set PLLM
    RCC->CFGR |= RCC_CFGR_PLLXTPRE_HSE; //set HSE division before PLL
    RCC->CFGR |= 0x01 << RCC_CFGR_PLLSRC_Pos;   // select source PLL = HSE
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;   // set AHB1 Prescaler -> 36 MHz
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;   // set AHB2 Prescaler -> 72 MHz
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;    // set AHB Prescaler -> 72 MHz
    RCC->CR |= RCC_CR_PLLON;    // PLL ON
    while (!(RCC->CR & RCC_CR_PLLRDY)); // wait PLL Ready Flag
    RCC->CFGR |= RCC_CFGR_SW_PLL;   // select source SYSCLK = PLL
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL));    // wait till PLL is used
}
