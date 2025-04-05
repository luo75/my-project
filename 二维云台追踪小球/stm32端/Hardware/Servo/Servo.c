#include "sys.h"

void Servo_Init(void)
{
	 PWM_Init();
}


/*

对于180°舵机
t = 0.5ms——————-舵机会转动 0 ° 
t = 1.0ms——————-舵机会转动 45°
t = 1.5ms——————-舵机会转动 90°
t = 2.0ms——————-舵机会转动 135°
t = 2.5ms——————-舵机会转动180
*/

void Servo_Down_Set(float Pwm)	//180度舵机	
{
	PWM_SetCompare1(Pwm);
}


void Servo_Up_Set(float Pwm)	//270度舵机
{
	PWM_SetCompare2(Pwm);
}
