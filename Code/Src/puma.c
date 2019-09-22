#include "puma.h"

extern const uint16_t PWM_period;

int val = 0;
float K_p = 0;
float K_i = 0;
uint32_t err_i = 0;

void PI_custom (int err) {

	err_i += err;
	if (err_i > 6000) {
		err_i = 6000;
    }
	if (err_i < -6000) {
		err_i = -6000;
	}
	val = K_p * err + K_i * err_i;
	if (val > 950) {
		val = 950;
    }
	if (val < -950) {
		val = -950;
	}
	TIM1->CCR1 = (uint32_t)(PWM_period/2 + val);
    TIM1->CCR2 = (uint32_t)(PWM_period/2 - val);
}

void Func_2 (volatile uint16_t *mass, pos_cycl *cur_pos_cycl) {
	
}