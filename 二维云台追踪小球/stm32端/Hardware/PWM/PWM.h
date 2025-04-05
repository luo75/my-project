#ifndef __PWM_H
#define __PWM_H

#include "sys.h"
void PWM_Init(void);	//PWM初始化
void PWM_SetCompare1(uint16_t Compare);	//设置TIM3,通道1的CCR的值
void PWM_SetCompare2(uint16_t Compare);	//设置TIM3,通道2的CCR的值
#endif
