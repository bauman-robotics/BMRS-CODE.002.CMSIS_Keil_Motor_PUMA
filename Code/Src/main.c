#include "main.h"

#define TEST0 1
#define TEST1 0

volatile uint16_t adc_val[2] = {0, 0};
pos_cycl position_cycle;
int w = 0;
int nes_val = 0;
int err = 0;


int main(void ) {	
    RCC_init();
	GPIO_init();
    TIM1_init();
    TIM2_ENCODE_init();
//    ADC1_init(adc_val);
	
	BRAKE_OFF;
    while (1) {
#if TEST1
		err = (uint16_t)(TIM2->CNT) - nes_val;
		PI_custom(err);
#endif
#if TEST0
		TIM1->CCR1 = 1000 + w;
		TIM1->CCR2 = 1000 - w;
#endif
    }
}
