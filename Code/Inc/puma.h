#ifndef __PUMA_H__
#define __PUMA_H__

#include "stm32f1xx.h"
#include "tim.h"

typedef struct {
	
}pos_cycl;


void Func_1 (uint32_t err, pos_cycl *cur_pos_cycl);
void Func_2 (volatile uint16_t *mass, pos_cycl *cur_pos_cycl);

#endif // __PUMA_H__
