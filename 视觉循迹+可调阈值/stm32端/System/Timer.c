#include "sys.h"                 // Device header
/********
��ʱ��1
����=TIM_Period*TIM_Prescaler/72000000
********/
#define Period (20)
#define Prescaler (7200)

void Timer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//����TIM2��ʱ��
	
	TIM_InternalClockConfig(TIM1);	//ʹ���ڲ�ʱ����ΪTIM1��ʱ��
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//�������ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = Period - 1;	//ARR�Զ���װ����ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler - 1;	//PSCԤ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	//�ظ���������ֵ���߼���ʱ������Ҫ�ã�
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);	//�ֶ�����жϱ�־λ��ֹ�ϵ��ֱ�ӽ����ж�
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);	//�����жϵ�NVIC��ͨ·
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//���ȼ�
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;	//�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM1, ENABLE);	//��ʱ��ʹ��
}



