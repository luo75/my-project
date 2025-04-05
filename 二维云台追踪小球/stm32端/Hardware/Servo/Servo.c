#include "sys.h"

void Servo_Init(void)
{
	 PWM_Init();
}


/*

����180����
t = 0.5ms������������-�����ת�� 0 �� 
t = 1.0ms������������-�����ת�� 45��
t = 1.5ms������������-�����ת�� 90��
t = 2.0ms������������-�����ת�� 135��
t = 2.5ms������������-�����ת��180
*/

void Servo_Down_Set(float Pwm)	//180�ȶ��	
{
	PWM_SetCompare1(Pwm);
}


void Servo_Up_Set(float Pwm)	//270�ȶ��
{
	PWM_SetCompare2(Pwm);
}
