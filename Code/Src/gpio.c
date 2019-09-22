#include "gpio.h"

void GPIO_init (void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    /***Clear all necessary bits***/
    GPIOA->CRL &= ~ (GPIO_CRL_CNF2_Msk);
    /******/
    GPIOA->CRL |= (0x01 << GPIO_CRL_MODE2_Pos);
}