#ifndef __TIM_H__
#define __TIM_H__

#include "stm32f1xx.h"

#define PWM_period 2000;

void TIM1_init(void);
void TIM2_ENCODE_init(void);

#endif // __TIM_H__
