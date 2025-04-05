#include "board.h"
#include "oled.h"
#include "LED.h"
#include "key.h"
#include "motor.h"
#include "Beep.h"
#include "Track.h"
/**************************************PID参数定义**********************************************/
float SpeedL_KP=290,SpeedL_KI=0,SpeedL_KD=0;			
float SpeedR_KP=300,SpeedR_KI=0,SpeedR_KD=0;

float Place_difference_k=10;	//左轮-右轮补偿系数
/**************************************PID参数整定**********************************************/

/***********************************************************************************************
	1、先增加速度环p，到刚刚出现不稳定的震动
	2、增加I，消除稳态误差。当停则停
	3、加入位置环，位置环仅加入P，到合适的精度即可
	
	注：停车的时候积分要清零	//增量式可能不用吧
************************************************************************************************/

/***************************************被测量*********************************************/	
float Left_Count=0,Right_Count=0;	//编码器数值
int16_t Encoder2, Encoder4;//编码器数值(速度)
int16_t Pulse2,Pulse4;//速度累加->位移
float Pitch,Roll,Yaw;
/***************************************设定值*********************************************/	
int Target_Speed2,Target_Speed4;	//目标速度
/**********************************************控制量****************************************/
int Track_Compensate=0;//循迹补偿
int Place_difference_compensate=0;	//左轮-右轮补偿
int Pwm_Out2=0,Pwm_Out4=0;	//速度环输出

/**********************************************标志位****************************************/
int key_temp=0;//按键暂存量
int task_flag=0;	//记录当前执行的是问题几，0代表不动作
int Place_compensate_Enable=0;	//（0不开启直线补偿，1开启）
int track_flag=0;
int task_finish_flag=0;	//任务完成标志
int bar=0;
int time_count=0;
int time_enable=0;	//蜂鸣器亮灯
int infty_loop=0;
int target_infty_loop=0;
//当前速度环没有采用积分
//int flag_speed=0;	//积分清零标志位(停车的时候积分要清零)
//int flag_place=0;	//积分清零标志位(停车的时候积分要清零)

/**********************************************函数声明****************************************/
int Speed_PID_L (int FeedBack,int Target);	//PID函数声明 采用的都是位置式PID
int Speed_PID_R (int FeedBack,int Target);

int main(void)
{
	//开发板初始化
	board_init();
	
	Beep_off();
	LED_off();  
	
	NVIC_ClearPendingIRQ(GPIO_MULTIPLE_GPIOB_INT_IRQN);	//清除编码器中断标志位
	NVIC_ClearPendingIRQ(Control_INST_INT_IRQN);//清除定时器中断标志位
    
	NVIC_EnableIRQ(GPIO_MULTIPLE_GPIOB_INT_IRQN);	//编码器中断使能
	NVIC_EnableIRQ(Control_INST_INT_IRQN);//使能定时器中断
/**********************************************初始化完成****************************************/

    while(1) //m0的运行速度慢的一批/
    { 
		//按键逻辑，一级判断
		key_temp=Key_GetNum();
		if(key_temp==1)
		{
			if(task_flag!=0)	//任务执行中，点击按键1取消任务
			{
				task_flag=0;
			}
			else
			{
				task_flag=1;
				Place_compensate_Enable=1;	//直线补偿使能
				Target_Speed2=Target_Speed4=10;	//设定速度
			}
			
		}
		else if(key_temp==2)
		{
			task_flag=2;
			Place_compensate_Enable=1;	//直线补偿使能
			Target_Speed2=Target_Speed4=10;	//设定速度
		}
		else if(key_temp==3)
		{
			task_flag=3;
			Place_compensate_Enable=1;	//直线补偿使能
			Target_Speed2=Target_Speed4=10;	//设定速度
			target_infty_loop=1;
		}
		else if(key_temp==4)
		{
			task_flag=4;
			Place_compensate_Enable=1;	//直线补偿使能
			Target_Speed2=Target_Speed4=10;	//设定速度
			target_infty_loop=4;
		}

    }
}

void TIMA1_IRQHandler(void)//定时器A1中断（10ms）控制程序写在这里
{
/**********************************************读取路程,速度，时间***********************************/
	Encoder2=Left_Count;
	Encoder4=Right_Count;	//读取速度
	Pulse2+=Encoder2;
	Pulse4+=Encoder4;	//读取路程

	Left_Count=0;
	Right_Count=0;	//清除编码器数值
	if(time_enable==1)
	{
		time_count++;
		if(time_count>100)
		{
			LED_off();
			Beep_off();
			time_enable=0;
			time_count=0;
		}
	}
/**********************************************************************************************/	
/**********************************************任务逻辑****************************************/
		if(task_flag!=0)
		{
			if(task_flag==1)	//当前为任务1
			{
				if(Pulse2>1900)
				{
					task_finish_flag=1;	//任务完成标志位1
					LED_on();
					Beep_on();
					time_enable=1;
				}
			}
			
			else if(task_flag==2)	//当前为任务2
			{	
				if(bar==0&&Pulse2>1850)	//go straight length
				{
					Place_compensate_Enable=0;
					track_flag=1;	//track enable
					Pulse2=Pulse4=0;	
					
					LED_on();
					Beep_on();
					time_enable=1;
					
					bar++;
				}		
				if(bar==1&&Pulse2>2200)	//track length
				{
					Place_compensate_Enable=0;
					track_flag=0;
					Pulse2=Pulse4=0;	
					
					LED_on();
					Beep_on();
					time_enable=1;
					
					Target_Speed2=14;	//turn right speed
					Target_Speed4=10;
					bar++;
				}	
				if(bar==2&&Pulse2>600)	//turn right rectify length
				{
					Place_compensate_Enable=1;
					track_flag=0;
					Pulse2=Pulse4=0;	
					
					Target_Speed2=10;	//speed normal
					Target_Speed4=10;
					bar++;
				}	
				if(bar==3&&Pulse2>1600)	//go straight length
				{
					Place_compensate_Enable=0;
					track_flag=1;
					Pulse2=Pulse4=0;	
					
					LED_on();
					Beep_on();
					time_enable=1;
					
					bar++;
				}				
				if(bar==4&&Pulse2>2000)	//track length
				{
					Place_compensate_Enable=0;
					track_flag=0;
					Pulse2=Pulse4=0;	//累计路程清零
					
					Target_Speed2=14;
					Target_Speed4=10;
					bar++;
				}
				if(bar==5&&Pulse2>500)	//turn right rectify length
				{
					Place_compensate_Enable=1;
					track_flag=0;
					Pulse2=Pulse4=0;	//累计路程清零
					
					LED_on();
					Beep_on();
					time_enable=1;
					
					task_finish_flag=1;
				}

			}
			else if(task_flag==3||task_flag==4)	//task3 or task4 
			{
				if(bar==0&&Pulse2>200)			//go straight first
				{
					Place_compensate_Enable=0;
					track_flag=0;
					Pulse2=Pulse4=0;	
					
					Target_Speed2=14;	//turn right speed
					Target_Speed4=10;
					bar++;
				}		
				if(bar==1&&Pulse2>600)	// turn right rectify length
				{
					Place_compensate_Enable=1;
					track_flag=0;
					Pulse2=Pulse4=0;	
					
					Target_Speed2=10;//speed normal
					Target_Speed4=10;
					bar++;
				}	
				if(bar==2&&Pulse2>1500)//go straight length
				{
					Place_compensate_Enable=0;
					track_flag=0;		//track start
					Pulse2=Pulse4=0;	
					
					LED_on();//led attention
					Beep_on();	
					time_enable=1;
					
					Target_Speed2=8;	//turn left speed
					Target_Speed4=14;
					bar++;
				}	
				if(bar==3&&Pulse2>400)//turn left rectify length
				{
					Place_compensate_Enable=0;
					track_flag=1;		//track start
					Pulse2=Pulse4=0;	
					
					Target_Speed2=10;//speed normal
					Target_Speed4=10;
					bar++;
				}	
				
				if(bar==4&&Pulse2>1700)	//track length
				{
					Place_compensate_Enable=0;
					track_flag=0;
					Pulse2=Pulse4=0;	
					
					LED_on();
					Beep_on();
					time_enable=1;
					
					Target_Speed2=8;	//turn left speed
					Target_Speed4=14;
					bar++;
				}
				
				if(bar==5&&Pulse2>350)	//turn left rectify length
				{
					Place_compensate_Enable=1;
					track_flag=0;
					Pulse2=Pulse4=0;	

					Target_Speed2=10;	//speed normal
					Target_Speed4=10;
					
					bar++;
				}
				if(bar==6&&Pulse2>1500)//go straight length
				{
					Place_compensate_Enable=0;
					track_flag=0;		
					Pulse2=Pulse4=0;	
					
					LED_on();	//lED Attention
					Beep_on();
					time_enable=1;
					
					Target_Speed2=14;//turn right speed
					Target_Speed4=8;
					bar++;
				}	
				if(bar==7&&Pulse2>800)//turn right rectify length
				{
					Place_compensate_Enable=0;
					track_flag=1;		
					Pulse2=Pulse4=0;	
					
					Target_Speed2=10;	//speed normal
					Target_Speed4=10;
					bar++;
				}	
				if(bar==8&&Pulse2>1900)//track length
				{
					Place_compensate_Enable=0;
					track_flag=0;		
					Pulse2=Pulse4=0;	
					
					LED_on();
					Beep_on();
					time_enable=1;
					
					Target_Speed2=14;	//turn right rectify length
					Target_Speed4=8;
					bar++;
				}	
				if(bar==9&&Pulse2>350)//the last rectify
				{
					infty_loop++;
					if(infty_loop>=target_infty_loop)
					{
						task_finish_flag=1;
					}
					else
					{
						Pulse2=Pulse4=0;
						Target_Speed2=10;	//normal speed
						Target_Speed4=10;
						bar=0;
					}
				}
					
			}
		}
		
		if(task_finish_flag==1)
		{
			Pwm_Out2=Pwm_Out4=0;	//装载速度清零
			Pulse2=Pulse4=0;	//累计路程清零
			task_finish_flag=0;
			task_flag=0;
			target_infty_loop=0;
			bar=0;
		}
/**********************************************************************************************/	
		
/**********************************************控制程序****************************************/
		if(task_flag!=0)	
		{
			if(Place_compensate_Enable==1)	//直线补偿使能
			{
				Place_difference_compensate=Place_difference_k*(Pulse2-Pulse4);	//直线差值补偿(可以更换陀螺仪闭环控制)
			}
			else
			{
				Place_difference_compensate=0;
			}
			if(track_flag==1)
			{
				Track_Enable();
			}
				
			Pwm_Out2=Speed_PID_L(Target_Speed2,Encoder2)-Place_difference_compensate;
			Pwm_Out4=Speed_PID_R(Target_Speed4,Encoder4)+Place_difference_compensate;
		}
		
		Load(Pwm_Out2,Pwm_Out4);	//装载函数
		
}
/***********************************************************************************************/
void GROUP1_IRQHandler(void)//Group1的中断服务函数
{	
/***************************************************************************************
			编码器程序
****************************************************************************************/
uint32_t gpioB_0 = DL_GPIO_getEnabledInterruptStatus(GPIOB,DL_GPIO_PIN_18);
uint32_t gpioB_1 = DL_GPIO_getEnabledInterruptStatus(GPIOB,DL_GPIO_PIN_20);
//编码器1
if(gpioB_1 & DL_GPIO_PIN_20)
{
	if((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_20) > 0) && (DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_24) == 0))
		Left_Count--;
	else if((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_20) == 0) && (DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_24) > 0))
		Left_Count--;
	
	else if((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_20) > 0) && (DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_24) > 0))
		Left_Count++;
	else if((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_20) == 0) && (DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_24) == 0))
		Left_Count++;
	DL_GPIO_clearInterruptStatus(GPIOB,DL_GPIO_PIN_20);	
}
	
//编码器2
if(gpioB_0 & DL_GPIO_PIN_18)
{
	if((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_18) > 0) && (DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_19) == 0))
		Right_Count++;
	else if((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_18) == 0) && (DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_19) > 0))
		Right_Count++;
	
	else if((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_18) > 0) && (DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_19) > 0))
		Right_Count--;
	else if((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_18) == 0) && (DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_19) == 0))
		Right_Count--;
	DL_GPIO_clearInterruptStatus(GPIOB,DL_GPIO_PIN_18);	
}
/***************************************************************************************/
	
}
/*************************
左轮速度位置式PID控制器
入口参数:反馈值，目标值
输出：控制量（PWM）
*************************/
int Speed_PID_L (int Target,int FeedBack )
{ 	
	int Pwm_Out;
	
	float SpeedL_err;
	
	static float SpeedL_Last_err,SpeedL_Sum;
	
//	if(flag_speed==1) {SpeedL_Sum=0;}	//积分清零
	SpeedL_err=Target-FeedBack;
	
	SpeedL_Sum+=SpeedL_err;
	
	Pwm_Out = SpeedL_KP*SpeedL_err + SpeedL_KI*SpeedL_Sum + SpeedL_KD*(SpeedL_err-SpeedL_Last_err);
	
	if(Pwm_Out>2000)
	{
		Pwm_Out=2000;
	}
	if(Pwm_Out<-2000)
	{
		Pwm_Out=-2000;
	}
	
	SpeedL_Last_err=SpeedL_err;
	
	return Pwm_Out;
}                                      
/*************************
右轮速度位置式PID控制器
入口参数:反馈值，目标值
输出：控制量（PWM）
*************************/
int Speed_PID_R (int Target,int FeedBack )
{ 	
	int Pwm_Out;
	
	float SpeedR_err;
	
	static float SpeedR_Last_err,SppedR_Sum;
	
//	if(flag_speed==1) {SppedR_Sum=0; flag_speed=0;}	//积分清零
	SpeedR_err=Target-FeedBack;
	
	SppedR_Sum+=SpeedR_err;
	
	Pwm_Out = SpeedR_KP*SpeedR_err + SpeedR_KI*SppedR_Sum + SpeedR_KD*(SpeedR_err-SpeedR_Last_err);
	
	if(Pwm_Out>2000)
	{
		Pwm_Out=2000;
	}
	if(Pwm_Out<-2000)
	{
		Pwm_Out=-2000;
	}
	
	SpeedR_Last_err=SpeedR_err;
	
	return Pwm_Out;
}






