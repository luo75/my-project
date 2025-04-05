#include "sys.h"
#include "Timer.h"
#include "usart.h"
#include "delay.h"
/***************************************************************************************
			�Ӿ����ڽ��յ����ݰ�
****************************************************************************************/
int usart1_RxPacket[5];
int Blob_Position[2];

/***************************************************************************************
				PID����
****************************************************************************************/
float	Kp_x=1.2,Kd_x=1.5;                                                                                            ;
float	Kp_y=0.8,Kd_y=1;

float X_PDout;
float Y_PDout;
/***************************************************************************************
				��������
****************************************************************************************/
float ServoX_PD_Calculate(int Target_Position,int Measure_Position);
float ServoY_PD_Calculate(int Target_Position,int Measure_Position);

/***************************************************************************************
				��������
****************************************************************************************/
int Key_Num=0;
int PWM_x=1500,PWM_y=500;
int Rx_Flag=0;
/****************************************************************************************/
int main(void)
{
	delay_init();			//�ӳٺ���
	
	Key_Init();				//������ʼ��
	
	OLED_Init();			//OLED
	OLED_Clear();
	
	Timer_Init();			//TIM1��ʱ���ж�

	usart1_Init(115200);	//����1��ʼ���������Ӿ�����
	

	Servo_Init();	//�����ʼ��
	
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
TIM1��ʱ���жϳ���10ms����
***********************************************************/
void TIM1_UP_IRQHandler()	//TIM1��ʱ���ж�
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)	//ȷ���жϱ�־λ
	{
		if(Rx_Flag==1)	//���յ���������PID����
		{
			X_PDout=ServoX_PD_Calculate(64,Blob_Position[0]);	//PID����
			Y_PDout=ServoY_PD_Calculate(80,Blob_Position[1]);
			
			PWM_x=PWM_x-X_PDout;	//��PID�����ֵ��Ϊ�������ӵ�ԭPWM�ϣ���������Ϊ���Է��ˣ�
			PWM_y=PWM_y-Y_PDout;
			
			Servo_Down_Set(PWM_x);	//���Է���
			Servo_Up_Set(PWM_y); 
			
			Rx_Flag=0;	//��������󽫱�־λ����
		}

	}
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);	//����жϱ�־λ
}

/**********************************************************
				usart1�жϳ���

				���ڽ���OpenMV/K210������
***********************************************************/
void USART1_IRQHandler(void)
{
	static int i=0;	//����һ���±�����������Ǿ�̬�ķ���ÿ�ν����жϺ���i���ᱻ���¶���
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
			usart1_RxPacket[i++] = USART_ReceiveData(USART1);
			
			if(usart1_RxPacket[0]!=0xa3) i=0;	//�ж�֡ͷ
		
			if((i==2&&usart1_RxPacket[1]!=0xb3)) i=0;
			
			if(i==5)	//�������
			{
				if(usart1_RxPacket[4]==0xc3)	//�ж�֡β
				{
					Blob_Position[0]=usart1_RxPacket[2];
					Blob_Position[1]=usart1_RxPacket[3];
				}
				Rx_Flag=1;	//���յ�����
				i=0; //�������
			}
	}
		
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//����жϱ�־λ
	
}

/**********************************************************
x����PD������
��ڲ�����Ŀ��λ�ã�����λ��
�����PWM
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
y����PD������
��ڲ�����Ŀ��λ�ã�����λ��
�����PWM
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
