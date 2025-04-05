#include "board.h"
#include "motor.h"
int PWM_MAX=3200;
int PWM_MIN=0;

/*赋值函数*/
/*入口参数：PID运算完成后的最终PWM值*/
void Load(int moto1,int moto2)
{
	//1.研究正负号，对应正反转
	if(moto1>0){DL_GPIO_setPins(Motor_pin_PORT,Motor_pin_AIN1_PIN); ;DL_GPIO_clearPins(Motor_pin_PORT,Motor_pin_AIN2_PIN);}//正转
	
	else 		{DL_GPIO_clearPins(Motor_pin_PORT,Motor_pin_AIN1_PIN); ;DL_GPIO_setPins(Motor_pin_PORT,Motor_pin_AIN2_PIN);}//反转
	
	//2.研究PWM值
	DL_TimerG_setCaptureCompareValue(TIMG7,abs(moto1),DL_TIMER_CC_0_INDEX);  //PA26
	
	//1.研究正负号，对应正反转
	if(moto2>0){DL_GPIO_setPins(Motor_pin_PORT,Motor_pin_BIN1_PIN); ;DL_GPIO_clearPins(Motor_pin_PORT,Motor_pin_BIN2_PIN);}//正转
	
	else 		{DL_GPIO_clearPins(Motor_pin_PORT,Motor_pin_BIN1_PIN); ;DL_GPIO_setPins(Motor_pin_PORT,Motor_pin_BIN2_PIN);}//反转

	//2.研究PWM值
	DL_TimerG_setCaptureCompareValue(TIMG7,abs(moto2),DL_TIMER_CC_1_INDEX);  //PA27
	
}