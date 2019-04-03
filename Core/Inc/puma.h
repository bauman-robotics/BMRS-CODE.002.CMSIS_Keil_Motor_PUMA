#ifndef __PUMA_H__
#define __PUMA_H__

#include "stm32f1xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

uint32_t turn_cnt = 0;

void Motor_Control(uint16_t mean);
float POT_GetAngle(void);
void Init_StartPosition(void);

#endif /* __PUMA_H__ */

