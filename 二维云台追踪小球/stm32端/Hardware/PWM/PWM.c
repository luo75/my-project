#include "stm32f10x.h"                  // Device header

void PWM_Init(void)	//50HZ
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//����GPIOB��TIM2��ʱ��
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//�����ؼ���
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);	//���ṹ�帳��ʼֵ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//ѡ��PWM1ģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//���Բ���ת
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//PWM���ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	//����Ƚ�ͨ��3��ʼ��
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM3, ENABLE);	//TIM3ʹ��
}

void PWM_SetCompare1(uint16_t Compare)	//�޸�ͨ��3��CCR��ֵ������ѡ������ž�����
{
	TIM_SetCompare1(TIM3, Compare);
}
void PWM_SetCompare2(uint16_t Compare)	//�޸�ͨ��3��CCR��ֵ������ѡ������ž�����
{
	TIM_SetCompare2(TIM3, Compare);
}
