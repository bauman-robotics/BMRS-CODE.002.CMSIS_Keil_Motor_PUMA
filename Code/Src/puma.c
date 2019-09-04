#include "puma.h"

extern const uint16_t PWM_period;

void Func_1 (uint32_t err, pos_cycl *cur_pos_cycl) {
	if (err > PWM_period/2) {
		err = PWM_period/2;
    } if (err < (- PWM_period/2)) {
		err = - PWM_period/2;
    }
	TIM1->CCR1 = (uint32_t)(PWM_period/2) + err;
    TIM1->CCR2 = (uint32_t)(PWM_period/2) - err;
}

void Func_2 (volatile uint16_t *mass, pos_cycl *cur_pos_cycl) {
	
}