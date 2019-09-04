#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f1xx.h"

void ADC1_init(volatile uint16_t *mas_adr);
uint16_t ADC1_GetValue(void);

#endif // __ADC_H__
