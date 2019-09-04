#include "adc.h"

void ADC1_init(volatile uint16_t *mas_adr) {
	#if 0
	/* Potentiometer`s ADC */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	// Enable port A clock
	RCC->CFGR &= ~ RCC_CFGR_ADCPRE;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;  // Set ADC Prescaler -> 12 MHz
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;	// Enable ADC clock
	/***Clear all necessary bits***/
	GPIOA->CRL &= ~GPIO_CRL_MODE0;
	GPIOA->CRL &= ~GPIO_CRL_CNF0;
	ADC1->CR2 &= ~ ADC_CR2_CONT;
	ADC1->CR2 &= ~ ADC_CR2_ALIGN;
	ADC1->SMPR2 &= ~ ADC_SMPR2_SMP0;
	ADC1->CR2 &= ~ ADC_CR2_EXTSEL;
	ADC1->SQR3 &= ~ ADC_SQR3_SQ1;
	ADC1->SQR1 &= ~ ADC_SQR1_L;
	/*****/
	
	GPIOA->CRL |= 0x00 << GPIO_CRL_MODE0_Pos;	// Input mode
	GPIOA->CRL |= 0x00 << GPIO_CRL_CNF0_Pos;	// Analog

	ADC1->CR2 |= ADC_CR2_CAL;	// Start calibration
	while (!(ADC1->CR2 & ADC_CR2_CAL));	// Wait end of calibration
  
	ADC1->CR2 |= ADC_CR2_ADON;	// Enable ADC and start conversion
	ADC1->CR2 &= ~ ADC_CR2_CONT; // Set one convertion mode
	ADC1->CR2 &= ~ ADC_CR2_ALIGN;	// Right alignment
	ADC1->SMPR2 &= ~ ADC_SMPR2_SMP0;	// Set 1.5 cycle
	ADC1->CR2 |= 0x07 << ADC_CR2_EXTSEL_Pos;	// Set SWSTART trigger
	ADC1->CR2 |= ADC_CR2_EXTTRIG;	// Enable external trigger
	ADC1->SQR3 &= ~ ADC_SQR3_SQ1;	// Channel 0 is setted first in convertion sequence
	ADC1->SQR1 &= ~ ADC_SQR1_L;	// 1 convertion
	#endif
	/* Potentiometer`s and Current`s ADC */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;							// Enable port A clock
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;							// Enable port B clock
	RCC->CFGR &= ~ RCC_CFGR_ADCPRE;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;  						// Set ADC Prescaler -> 12 MHz
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;							// Enable ADC clock
	/***Clear all necessary bits***/		
	GPIOA->CRL &= ~GPIO_CRL_MODE0;
	GPIOA->CRL &= ~GPIO_CRL_CNF0;
	ADC1->CR2 &= ~ ADC_CR2_CONT;
	ADC1->CR2 &= ~ ADC_CR2_ALIGN;
	ADC1->SMPR2 &= ~ (ADC_SMPR2_SMP0 |ADC_SMPR2_SMP0);
	ADC1->CR2 &= ~ ADC_CR2_EXTSEL;
	ADC1->SQR3 &= ~ ADC_SQR3_SQ1;
	ADC1->SQR3 &= ~ ADC_SQR3_SQ2;
	ADC1->SQR1 &= ~ ADC_SQR1_L;
	ADC1->CR2 &= ~ ADC_CR2_DMA;
	/*****/
	
	GPIOA->CRL |= 0x00 << GPIO_CRL_MODE0_Pos;					// Input mode
	GPIOA->CRL |= 0x00 << GPIO_CRL_CNF0_Pos;					// Analog
	
	GPIOB->CRL |= 0x00 << GPIO_CRL_MODE1_Pos;					// Input mode
	GPIOB->CRL |= 0x00 << GPIO_CRL_CNF1_Pos;					// Analog

	ADC1->CR2 |= ADC_CR2_CAL;									// Start calibration
	while (!(ADC1->CR2 & ADC_CR2_CAL));							// Wait end of calibration
  
	ADC1->CR2 |= ADC_CR2_ADON;									// Enable ADC and start conversion
	ADC1->CR2 &= ~ ADC_CR2_CONT; 								// Set one convertion mode
	ADC1->CR2 &= ~ ADC_CR2_ALIGN;								// Right alignment
	ADC1->SMPR2 &= ~ (ADC_SMPR2_SMP0 | ADC_SMPR2_SMP1);			// Set 1.5 cycle on channel 0 and 1
	ADC1->CR2 |= 0x07 << ADC_CR2_EXTSEL_Pos;					// Set SWSTART trigger
	ADC1->CR2 |= ADC_CR2_EXTTRIG;								// Enable external trigger
	ADC1->SQR3 &= ~ ADC_SQR3_SQ1;								// Channel 0 is setted first in convertion sequence
	ADC1->SQR3 |= (0x01 << ADC_SQR3_SQ2_Pos);					// Channel 1 is setted second in convertion sequence
	ADC1->SQR1 |= (0x01 << ADC_SQR1_L_Pos);						// 2 convertion
	
	ADC1->CR1 |= ADC_CR1_SCAN; 									// Enable SCAN mode
	ADC1->CR2 |= ADC_CR2_DMA;									// Enable DMA		
	/**** DMA ****/
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;							// Enable DMA1
	/***Clear all necessary bits***/		
	DMA1_Channel1->CCR &= ~ 0x7FFF;
	DMA1_Channel1->CPAR &= ~ DMA_CPAR_PA;
	DMA1_Channel1->CMAR &= ~ DMA_CMAR_MA;
	DMA1_Channel1->CNDTR &= ~ DMA_CNDTR_NDT;
	/*****/
	DMA1_Channel1->CPAR |= (uint32_t)(&ADC1->DR);				// Peripheral address
	DMA1_Channel1->CMAR |= (uint32_t)mas_adr;					// Memory address
	DMA1_Channel1->CNDTR |= 0x02;								// Total number of date
	DMA1_Channel1->CCR |= (0x01 << DMA_CCR_PL_Pos);				// Set priority
	DMA1_Channel1->CCR &= ~ DMA_CCR_DIR;						// Data transfer direction
	DMA1_Channel1->CCR |= DMA_CCR_CIRC;							// Enable circular mode
	DMA1_Channel1->CCR &= ~ DMA_CCR_PINC;						// Diseble peripheral increment mode
	DMA1_Channel1->CCR |= DMA_CCR_MINC;							// Enable memory increment mode
	DMA1_Channel1->CCR |= (0x01 << DMA_CCR_PSIZE_Pos);			// 16-bits
	DMA1_Channel1->CCR |= (0x01 << DMA_CCR_MSIZE_Pos);			// 16-bits
	DMA1_Channel1->CCR |= DMA_CCR_EN;							// Enable DMA1 Channel_1
}

