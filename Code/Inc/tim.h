#ifndef __TIM_H__
#define __TIM_H__

#include "stm32f1xx.h"

#define PWM_PERIOD			2000
#define HALF_PREIOD 		1000

void TIM1_init(void);
void TIM2_ENCODE_init(void);
void TIM3_init(void);
void TIM3_IRQHandler(void);

#endif // __TIM_H__
