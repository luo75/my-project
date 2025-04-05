#include "sys.h"
#include "Timer.h"
#include "usart.h"
#include "delay.h"
/***************************************************************************************
			视觉串口接收的数据包
****************************************************************************************/
int usart1_RxPacket[5];
int Blob_Position[2];

/***************************************************************************************
				PID参数
****************************************************************************************/
float	Kp_x=1.2,Kd_x=1.5;                                                                                            ;
float	Kp_y=0.8,Kd_y=1;

float X_PDout;
float Y_PDout;
/***************************************************************************************
				函数声明
****************************************************************************************/
float ServoX_PD_Calculate(int Target_Position,int Measure_Position);
float ServoY_PD_Calculate(int Target_Position,int Measure_Position);

/***************************************************************************************
				其他变量
****************************************************************************************/
int Key_Num=0;
int PWM_x=1500,PWM_y=500;
int Rx_Flag=0;
/****************************************************************************************/
int main(void)
{
	delay_init();			//延迟函数
	
	Key_Init();				//按键初始化
	
	OLED_Init();			//OLED
	OLED_Clear();
	
	Timer_Init();			//TIM1定时器中断

	usart1_Init(115200);	//串口1初始化，用于视觉串口
	

	Servo_Init();	//舵机初始化
	
	OLED_ShowString(0,0,"PWM_x:",12);
	OLED_ShowString(0,2,"PWM_y:",12);
	
	Blob_Position[0]=64;
	Blob_Position[1]=80;
	
	while(1)
	{		
		OLED_Float(0,50,PWM_x,1);
		OLED_Float(2,50,PWM_y,1);
		
	}
		
}	


/**********************************************************
TIM1定时器中断程序（10ms）：
***********************************************************/
void TIM1_UP_IRQHandler()	//TIM1定时器中断
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)	//确定中断标志位
	{
		if(Rx_Flag==1)	//接收到数据再做PID运算
		{
			X_PDout=ServoX_PD_Calculate(64,Blob_Position[0]);	//PID计算
			Y_PDout=ServoY_PD_Calculate(80,Blob_Position[1]);
			
			PWM_x=PWM_x-X_PDout;	//将PID计算的值作为增量增加到原PWM上（负号是因为极性反了）
			PWM_y=PWM_y-Y_PDout;
			
			Servo_Down_Set(PWM_x);	//极性反了
			Servo_Up_Set(PWM_y); 
			
			Rx_Flag=0;	//运算结束后将标志位清零
		}

	}
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);	//清除中断标志位
}

/**********************************************************
				usart1中断程序：

				用于接收OpenMV/K210的数据
***********************************************************/
void USART1_IRQHandler(void)
{
	static int i=0;	//定义一个下标变量，必须是静态的否则每次进入中断函数i都会被重新定义
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
			usart1_RxPacket[i++] = USART_ReceiveData(USART1);
			
			if(usart1_RxPacket[0]!=0xa3) i=0;	//判断帧头
		
			if((i==2&&usart1_RxPacket[1]!=0xb3)) i=0;
			
			if(i==5)	//接收完毕
			{
				if(usart1_RxPacket[4]==0xc3)	//判断帧尾
				{
					Blob_Position[0]=usart1_RxPacket[2];
					Blob_Position[1]=usart1_RxPacket[3];
				}
				Rx_Flag=1;	//接收到数据
				i=0; //清空数组
			}
	}
		
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//清除中断标志位
	
}

/**********************************************************
x轴舵机PD控制器
入口参数：目标位置，测量位置
输出：PWM
***********************************************************/
float ServoX_PD_Calculate(int Target_Position,int Measure_Position)
{
	float PWM;
	int err_x;
	static int Last_err_x;
	
	err_x=Target_Position-Measure_Position;
	
	
	PWM=Kp_x*err_x+Kd_x*(err_x-Last_err_x);
	
	Last_err_x=err_x;
	
	return PWM;
}

/**********************************************************
y轴舵机PD控制器
入口参数：目标位置，测量位置
输出：PWM
***********************************************************/
float ServoY_PD_Calculate(int Target_Position,int Measure_Position)
{
	float PWM;
	int err_y;
	static int Last_err_y;
	
	err_y=Target_Position-Measure_Position;
	
	PWM=Kp_y*err_y+Kd_y*(err_y-Last_err_y);
	
	Last_err_y=err_y;
	
	return PWM;
}
