#ifndef __PWM_H
#define __PWM_H

#include "sys.h"
void PWM_Init(void);	//PWM��ʼ��
void PWM_SetCompare1(uint16_t Compare);	//����TIM3,ͨ��1��CCR��ֵ
void PWM_SetCompare2(uint16_t Compare);	//����TIM3,ͨ��2��CCR��ֵ
#endif
