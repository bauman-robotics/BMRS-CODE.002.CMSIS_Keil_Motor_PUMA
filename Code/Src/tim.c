#include "tim.h"

void TIM1_init(void) {
    /* Complementary outputs */ 
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    /*** Clear all necessary bits ***/
    GPIOA->CRH &= ~ (GPIO_CRH_MODE8 | GPIO_CRH_MODE9 | GPIO_CRH_CNF8 | GPIO_CRH_CNF9);
    GPIOB->CRH &= ~ (GPIO_CRH_MODE13 | GPIO_CRH_MODE14 | GPIO_CRH_CNF13 | GPIO_CRH_CNF14);
    TIM1->ARR &= ~ TIM_ARR_ARR;
    TIM1->CCR1 &= ~ TIM_CCR1_CCR1;
    TIM1->CCR2 &= ~ TIM_CCR2_CCR2;
    TIM1->PSC &= ~ TIM_PSC_PSC;
    TIM1->CCMR1 &= ~ (TIM_CCMR1_OC1M | TIM_CCMR1_OC2M);
    TIM1->CR1 &= ~ (TIM_CR1_CMS | TIM_CR1_DIR | TIM_CR1_CEN);
    TIM1->BDTR &= ~ TIM_BDTR_DTG;
    /******/
    AFIO->MAPR &= ~ AFIO_MAPR_TIM1_REMAP;                                                   // No remap
    /*** Config pins A8, A9 & B13, B14 | Alternate function output Push-pull, max speed ***/
    GPIOA->CRH |= ((0x03 << GPIO_CRH_MODE8_Pos) | (0x03 << GPIO_CRH_MODE9_Pos));    
    GPIOA->CRH |= ((0x02 << GPIO_CRH_CNF8_Pos) | (0x02 << GPIO_CRH_CNF9_Pos));      
    GPIOB->CRH |= ((0x03 << GPIO_CRH_MODE13_Pos) | (0x03 << GPIO_CRH_MODE14_Pos));  
    GPIOB->CRH |= ((0x02 << GPIO_CRH_CNF13_Pos) | (0x02 << GPIO_CRH_CNF14_Pos));      
    /******/
    TIM1->ARR |= PWM_PERIOD;                                                                // Auto-reload register
    TIM1->CCR1 |= 0x00;                                                                     // Capture/compare register 1 
    TIM1->CCR2 |= 0x00;                                                                     // Capture/compare register 2
    TIM1->PSC |= 0x01;                                                                      // Prescaler  

    TIM1->CCMR1 |= ((0x06 << TIM_CCMR1_OC1M_Pos) | (0x06 << TIM_CCMR1_OC2M_Pos));           // Set PWM mode 1 on Channel 1, 2
    TIM1->CCMR1 |= (TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE);                                     // Enable preload register on TIM1_CCR1, TIM1_CCR2
    TIM1->CR1 |= TIM_CR1_ARPE;                          									// TIM1_ARR register is buffered  
    TIM1->CR1 &= ~ TIM_CR1_CMS;                        										// Edge-aligned mode
    TIM1->CR1 &= ~ TIM_CR1_DIR;                         									// Upcounter
    TIM1->CCER &= ~ (TIM_CCER_CC1P | TIM_CCER_CC1NP); 										// Set polarity on Channel 1, 1N, 
	TIM1->CCER  &= ~ (TIM_CCER_CC2P | TIM_CCER_CC2NP); 										// Set polarity on Channel 2, 2N
    TIM1->BDTR |= 0x24 << TIM_BDTR_DTG_Pos;             									// Dead time ~ 500 ns , t_dts = 1/72 000 000

    TIM1->BDTR |= TIM_BDTR_MOE;                         									// Enable main output
    TIM1->CCER |= ((TIM_CCER_CC1E | TIM_CCER_CC1NE) | (TIM_CCER_CC2E | TIM_CCER_CC2NE));    // On - OC1 and OC1N, OC2 and OC2N
    TIM1->EGR |= TIM_EGR_UG;    															// Reinitialize the counter and generates an update of the registers
    TIM1->CR1 |= TIM_CR1_CEN;   															// Enable counter

    TIM1->CCR1 = (uint32_t)(PWM_PERIOD / 2);                                                // Channel A
    TIM1->CCR2 = (uint32_t)(PWM_PERIOD / 2);                                                // Channel B
}

void TIM2_ENCODE_init(void) {
    /* Encode mode */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    /*** Clear all necessary bits ***/
    GPIOA->CRH &= ~ GPIO_CRH_MODE15;
    GPIOA->CRH &= ~ GPIO_CRH_CNF15;
    GPIOB->CRL &= ~ GPIO_CRL_MODE3;
    GPIOB->CRL &= ~ GPIO_CRL_CNF3;
    TIM2->ARR &= ~ TIM_ARR_ARR;
    TIM2->PSC &= ~ TIM_PSC_PSC;
    TIM2->SMCR &= ~ TIM_SMCR_SMS;
    TIM2->CR1 &= ~ TIM_CR1_CEN;
    TIM2->CCMR1 &= ~ (TIM_CCMR1_IC1F | TIM_CCMR1_IC2F);
    TIM2->CCER &= ~ (TIM_CCER_CC1E | TIM_CCER_CC2E);
    /******/
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;      											// Release pin A15
    AFIO->MAPR |= 0x01 << AFIO_MAPR_TIM2_REMAP_Pos;     										// Remap to A15, B3
    /*** Config pins A15 & B3 | Floating input ***/
    GPIOA->CRH &= ~ GPIO_CRH_MODE15;
    GPIOA->CRH |= 0x01 << GPIO_CRH_CNF15_Pos;
    GPIOB->CRL &= ~ GPIO_CRL_MODE3;
    GPIOB->CRL |= 0x01 << GPIO_CRL_CNF3_Pos;
    /******/
    TIM2->ARR |= 0xFFFF;          																// Auto-reload register
    TIM2->PSC |= 0x00;       /* Don`t use */  																	// Prescaler
    TIM2->SMCR |= 0x03 << TIM_SMCR_SMS_Pos;            											// Set Encoder mode 3
    TIM2->CCER &= ~ (TIM_CCER_CC1P | TIM_CCER_CC2P);    										// Set polarity
	#ifdef INVERT_ENCODE_VECTOR
	TIM2->CCER |= TIM_CCER_CC1P; 																// Set polarity on channel 1
	TIM2->CCER &= ~ TIM_CCER_CC2P; 																// Set polarity on channel 2
	#endif
    TIM2->CCMR1 &= ~ (TIM_CCMR1_IC1F | TIM_CCMR1_IC2F); 										// Set input filter
    TIM2->CCMR1 |= ((0x01 << TIM_CCMR1_CC1S_Pos) | (0x01 << TIM_CCMR1_CC2S_Pos));   			// Configurate input capture
    TIM2->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E);      										// Capture enabled
    TIM2->CR1 |= TIM_CR1_CEN;   																// Enable counter
    TIM2->CNT = 0;
}

void TIM3_init(void) {
    /* Timer mode, 1ms*/
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    /*** Clear all necessary bits ***/
    TIM3->ARR &= ~ TIM_ARR_ARR;          													
    TIM3->PSC &= ~ TIM_PSC_PSC; 
    TIM3->CR1 &= ~ TIM_CR1_CEN;
    /******/
    TIM3->ARR |= 0x3E7;          															// Auto-reload register, 1000
    TIM3->PSC |= 0x47;                                                                      // Prescaler, 72
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1 |= TIM_CR1_CEN;                                                               // Enable counter

    NVIC_EnableIRQ(TIM3_IRQn);
}

__weak void TIM3_IRQHandler(void) {
}
