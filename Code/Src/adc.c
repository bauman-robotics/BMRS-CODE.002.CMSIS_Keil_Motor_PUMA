#include "adc.h"

void ADC1_init(void) {
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
}

uint16_t ADC1_GetValue(void) {
	static uint16_t tmp;
	ADC1->CR2 |= ADC_CR2_SWSTART;
	while (!(ADC1->SR & ADC_SR_EOC));
	tmp = ADC1->DR & ADC_DR_DATA;
	return tmp;
}
