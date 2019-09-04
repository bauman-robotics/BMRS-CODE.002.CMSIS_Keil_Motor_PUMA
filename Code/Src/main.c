#include "main.h"

volatile uint16_t adc_val[2] = {0, 0};
pos_cycl position_cycle;

 
int w = 0;

int main(void ) {	
    RCC_init();
    TIM1_init();
//    TIM2_ENCODE_init();
//    ADC1_init(adc_val);
		TIM1->CCR1 = 0; // A
		TIM1->CCR2 = 0; // B
    while (1) {
		TIM1->CCR1 = 1000 + w; // A
		TIM1->CCR2 = 1000 - w; // B
    }
}
