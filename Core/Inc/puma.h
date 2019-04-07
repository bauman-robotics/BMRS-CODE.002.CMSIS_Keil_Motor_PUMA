#ifndef __PUMA_H__
#define __PUMA_H__

#include "stm32f1xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

void Motor_Control(uint16_t mean);
void Init_StartPosition(void);
float POT_GetAngle(void);
float ENC_GetVelocity(void);

#endif /* __PUMA_H__ */

