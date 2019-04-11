#include "puma.h"

uint8_t v_flag = 0;
uint32_t turn_cnt = 0;
float angle_init = 0.0;
float adc_angle;

float POT_GetAngle(void) {
	static uint16_t adc_angle_raw;

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	adc_angle_raw = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	adc_angle = 8.791208791208791 * adc_angle_raw;  // (360 * Max turns(100)) / Max adc(4095)
	return adc_angle;
}

void Rotation_Left(void){
	if (!((IN_A_GPIO_Port->ODR & IN_A_Pin) && !(IN_B_GPIO_Port->ODR & IN_B_Pin))) {
		TIM3->CCR3 = 0;		// Stop
		HAL_GPIO_WritePin(IN_A_GPIO_Port, IN_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(IN_B_GPIO_Port, IN_B_Pin, GPIO_PIN_RESET);
	}
}
	

void Rotation_Right(void) {
	if (!(!(IN_A_GPIO_Port->ODR & IN_A_Pin) && (IN_B_GPIO_Port->ODR & IN_B_Pin))) {
		TIM3->CCR3 = 0;		// Stop
		HAL_GPIO_WritePin(IN_A_GPIO_Port, IN_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(IN_B_GPIO_Port, IN_B_Pin, GPIO_PIN_SET);
	}
}

void Init_StartPosition (void) {

	angle_init = POT_GetAngle();
	
	if (angle_init < 18000) Rotation_Right();
	else {
		Rotation_Left();
		angle_init = 36000 - angle_init;
	}
	while (angle_init != 0) {
		TIM3->CCR3 = (uint16_t)(angle_init*0.0555555555555556); // PWM Period(1000)/(Max angle(36000)/2)
		angle_init = POT_GetAngle();
		if (angle_init > 18000) angle_init = 36000 - angle_init;
	}
	TIM3->CCR3 = 0;
	turn_cnt = 0;
	TIM4->CNT = 0;
}

void Motor_Control(uint16_t angle_error){
  static uint16_t pwr;
	pwr = (uint16_t)(angle_error*0.0555555555555556); 
	TIM3->CCR3 = pwr;
}

void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){
	if (GPIO_Pin == GPIO_PIN_4){
		turn_cnt++;
	}
}

float ENC_GetVelocity(void){
	static float velocity = 0;
	if (v_flag) {
		static uint16_t before_cnt = 0;
		static uint16_t current_cnt = 0;
		current_cnt = TIM4->CNT;
		velocity = (current_cnt - before_cnt) * 0.0114997604216579;		// 360 / (250 * 2 * 62.61)
		before_cnt = current_cnt;
		v_flag = 0;
	}
	return velocity;
}

void HAL_SYSTICK_Callback(void){
	static uint16_t i = 0;
	i++;
	if (i == 1000) {
		v_flag = 1;
		i = 0;
	}
}
