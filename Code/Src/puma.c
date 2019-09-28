#include "puma.h"


#define BIG_MOTOR 		1
#define SMALL_MOTOR		0

int val = 0;
int err_i = 0;
#if BIG_MOTOR
float K_p = 0;
float K_i = 0;
#endif
#if SMALL_MOTOR
float K_p = 0;
float K_i = 0;
#endif

void PI_custom (int err) {
	if (err > 32768) {
		err = 32768 - err;
	}
	if (err < -32768) {
		err = 65535 + err;
	}
	
	err_i += err;
	
	if (err_i > 6000) {
		err_i = 6000;
    }
	if (err_i < -6000) {
		err_i = -6000;
	}
	
	val = K_p * err + K_i * err_i * 0.001;
	
	if (val > HALF_PREIOD) {
		val = HALF_PREIOD;
    }
	if (val < -HALF_PREIOD) {
		val = -HALF_PREIOD;
	}
	TIM1->CCR1 = (uint32_t)(HALF_PREIOD - val);
    TIM1->CCR2 = (uint32_t)(HALF_PREIOD + val);
}
