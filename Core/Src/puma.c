#include "puma.h"

uint8_t v_flag = 0;
uint32_t turn_cnt = 0;

float POT_GetAngle(void) {
	static uint16_t adc_angle_raw;
	static float adc_angle;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	adc_angle_raw = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	adc_angle = 0.1404122151606579 * adc_angle_raw;  // (360 * Max turns(100))/(Max adc(4095) * Ratio(62.61))
	return adc_angle;
}

void Rotation_Right(void){
	TIM3->CCR3 = 0;		// Stop
	HAL_GPIO_WritePin(IN_A_GPIO_Port, IN_A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN_B_GPIO_Port, IN_B_Pin, GPIO_PIN_RESET);
}

void Rotation_Left(void) {
	TIM3->CCR3 = 0;		// Stop
	HAL_GPIO_WritePin(IN_A_GPIO_Port, IN_A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN_B_GPIO_Port, IN_B_Pin, GPIO_PIN_SET);
}

void Init_StartPosition (void) {
	static float angle;
	angle = POT_GetAngle();
	if (angle < 288) Rotation_Right();
	else {
		Rotation_Left();
		angle = 574.9880210828941 - angle;
	}
	while (angle != 0) {
		TIM3->CCR3 = (uint16_t)(angle*3.478333333333333); // PWM Period(1000)/(Max angle(574.9880210828941)/2)
		angle = POT_GetAngle();
	}
	turn_cnt = 0;
	TIM4->CNT = 0;
}
/*
void Motor_Control(uint16_t mean){
	static float angle, angle_error;
  static uint8_t pwr;
  angle =	POT_GetAngle();
	angle_error = mean - angle;	
 
  	TIM3->CCR3 = pwr;
}
*/
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
		velocity = (current_cnt - before_cnt) * 0.0110574619439018;		// 360 / (260 * 2 * 62.61)
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
