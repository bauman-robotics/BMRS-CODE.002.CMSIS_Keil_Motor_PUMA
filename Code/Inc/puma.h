#ifndef __PUMA_H__
#define __PUMA_H__

#include "stm32f1xx.h"
#include "tim.h"

#define BRAKE_ON 			GPIOA->BSRR = GPIO_BSRR_BR2
#define BRAKE_OFF			GPIOA->BSRR = GPIO_BSRR_BS2

typedef struct {
	
}pos_cycl;


void PI_custom (int err);


#endif // __PUMA_H__
