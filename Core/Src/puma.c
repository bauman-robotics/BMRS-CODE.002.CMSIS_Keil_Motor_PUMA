#include "puma.h"


float POT_GetAngle(void) {
	static uint16_t adc_angle_raw;
	static float adc_angle;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	adc_angle_raw = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	adc_angle = 0.1404122151606579 * adc_angle_raw;  // (360 * 100)/(4095 * 62.61)
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
		TIM3->CCR3 = (uint16_t)(angle*3.478333333333333); // 1000/(574.9880210828941/2)
		angle = POT_GetAngle();
	}
	turn_cnt = 0;
}

void Motor_Control(uint16_t mean){
	static float angle, angle_error;
  	static uint8_t pwr;
  	angle =	POT_GetAngle();
	angle_error = mean - angle;	
 
  	TIM3->CCR3 = pwr;
}

void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){
	if (GPIO_Pin == GPIO_PIN_4){
		turn_cnt++;
	}
}
