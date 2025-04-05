#include "sys.h"                 // Device header
/********
定时器1
周期=TIM_Period*TIM_Prescaler/72000000
********/
#define Period (20)
#define Prescaler (7200)

void Timer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//开启TIM2的时钟
	
	TIM_InternalClockConfig(TIM1);	//使用内部时钟作为TIM1的时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//采用向上计数
	TIM_TimeBaseInitStructure.TIM_Period = Period - 1;	//ARR自动重装器的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler - 1;	//PSC预分频器
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	//重复计数器的值（高级定时器才需要用）
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);	//手动清除中断标志位防止上电后直接进入中断
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);	//更新中断到NVIC的通路
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//优先级
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;	//中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	//响应优先级
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM1, ENABLE);	//定时器使能
}



