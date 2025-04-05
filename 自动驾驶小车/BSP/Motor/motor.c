#include "board.h"
#include "motor.h"
int PWM_MAX=3200;
int PWM_MIN=0;

/*��ֵ����*/
/*��ڲ�����PID������ɺ������PWMֵ*/
void Load(int moto1,int moto2)
{
	//1.�о������ţ���Ӧ����ת
	if(moto1>0){DL_GPIO_setPins(Motor_pin_PORT,Motor_pin_AIN1_PIN); ;DL_GPIO_clearPins(Motor_pin_PORT,Motor_pin_AIN2_PIN);}//��ת
	
	else 		{DL_GPIO_clearPins(Motor_pin_PORT,Motor_pin_AIN1_PIN); ;DL_GPIO_setPins(Motor_pin_PORT,Motor_pin_AIN2_PIN);}//��ת
	
	//2.�о�PWMֵ
	DL_TimerG_setCaptureCompareValue(TIMG7,abs(moto1),DL_TIMER_CC_0_INDEX);  //PA26
	
	//1.�о������ţ���Ӧ����ת
	if(moto2>0){DL_GPIO_setPins(Motor_pin_PORT,Motor_pin_BIN1_PIN); ;DL_GPIO_clearPins(Motor_pin_PORT,Motor_pin_BIN2_PIN);}//��ת
	
	else 		{DL_GPIO_clearPins(Motor_pin_PORT,Motor_pin_BIN1_PIN); ;DL_GPIO_setPins(Motor_pin_PORT,Motor_pin_BIN2_PIN);}//��ת

	//2.�о�PWMֵ
	DL_TimerG_setCaptureCompareValue(TIMG7,abs(moto2),DL_TIMER_CC_1_INDEX);  //PA27
	
}