#include "board.h"
#include "oled.h"
#include "LED.h"
#include "key.h"
#include "motor.h"
#include "Beep.h"
#include "Track.h"
/**************************************PID��������**********************************************/
float SpeedL_KP=290,SpeedL_KI=0,SpeedL_KD=0;			
float SpeedR_KP=300,SpeedR_KI=0,SpeedR_KD=0;

float Place_difference_k=10;	//����-���ֲ���ϵ��
/**************************************PID��������**********************************************/

/***********************************************************************************************
	1���������ٶȻ�p�����ոճ��ֲ��ȶ�����
	2������I��������̬����ͣ��ͣ
	3������λ�û���λ�û�������P�������ʵľ��ȼ���
	
	ע��ͣ����ʱ�����Ҫ����	//����ʽ���ܲ��ð�
************************************************************************************************/

/***************************************������*********************************************/	
float Left_Count=0,Right_Count=0;	//��������ֵ
int16_t Encoder2, Encoder4;//��������ֵ(�ٶ�)
int16_t Pulse2,Pulse4;//�ٶ��ۼ�->λ��
float Pitch,Roll,Yaw;
/***************************************�趨ֵ*********************************************/	
int Target_Speed2,Target_Speed4;	//Ŀ���ٶ�
/**********************************************������****************************************/
int Track_Compensate=0;//ѭ������
int Place_difference_compensate=0;	//����-���ֲ���
int Pwm_Out2=0,Pwm_Out4=0;	//�ٶȻ����

/**********************************************��־λ****************************************/
int key_temp=0;//�����ݴ���
int task_flag=0;	//��¼��ǰִ�е������⼸��0��������
int Place_compensate_Enable=0;	//��0������ֱ�߲�����1������
int track_flag=0;
int task_finish_flag=0;	//������ɱ�־
int bar=0;
int time_count=0;
int time_enable=0;	//����������
int infty_loop=0;
int target_infty_loop=0;
//��ǰ�ٶȻ�û�в��û���
//int flag_speed=0;	//���������־λ(ͣ����ʱ�����Ҫ����)
//int flag_place=0;	//���������־λ(ͣ����ʱ�����Ҫ����)

/**********************************************��������****************************************/
int Speed_PID_L (int FeedBack,int Target);	//PID�������� ���õĶ���λ��ʽPID
int Speed_PID_R (int FeedBack,int Target);

int main(void)
{
	//�������ʼ��
	board_init();
	
	Beep_off();
	LED_off();  
	
	NVIC_ClearPendingIRQ(GPIO_MULTIPLE_GPIOB_INT_IRQN);	//����������жϱ�־λ
	NVIC_ClearPendingIRQ(Control_INST_INT_IRQN);//�����ʱ���жϱ�־λ
    
	NVIC_EnableIRQ(GPIO_MULTIPLE_GPIOB_INT_IRQN);	//�������ж�ʹ��
	NVIC_EnableIRQ(Control_INST_INT_IRQN);//ʹ�ܶ�ʱ���ж�
/**********************************************��ʼ�����****************************************/

    while(1) //m0�������ٶ�����һ��/
    { 
		//�����߼���һ���ж�
		key_temp=Key_GetNum();
		if(key_temp==1)
		{
			if(task_flag!=0)	//����ִ���У��������1ȡ������
			{
				task_flag=0;
			}
			else
			{
				task_flag=1;
				Place_compensate_Enable=1;	//ֱ�߲���ʹ��
				Target_Speed2=Target_Speed4=10;	//�趨�ٶ�
			}
			
		}
		else if(key_temp==2)
		{
			task_flag=2;
			Place_compensate_Enable=1;	//ֱ�߲���ʹ��
			Target_Speed2=Target_Speed4=10;	//�趨�ٶ�
		}
		else if(key_temp==3)
		{
			task_flag=3;
			Place_compensate_Enable=1;	//ֱ�߲���ʹ��
			Target_Speed2=Target_Speed4=10;	//�趨�ٶ�
			target_infty_loop=1;
		}
		else if(key_temp==4)
		{
			task_flag=4;
			Place_compensate_Enable=1;	//ֱ�߲���ʹ��
			Target_Speed2=Target_Speed4=10;	//�趨�ٶ�
			target_infty_loop=4;
		}

    }
}

void TIMA1_IRQHandler(void)//��ʱ��A1�жϣ�10ms�����Ƴ���д������
{
/**********************************************��ȡ·��,�ٶȣ�ʱ��***********************************/
	Encoder2=Left_Count;
	Encoder4=Right_Count;	//��ȡ�ٶ�
	Pulse2+=Encoder2;
	Pulse4+=Encoder4;	//��ȡ·��

	Left_Count=0;
	Right_Count=0;	//�����������ֵ
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
/**********************************************�����߼�****************************************/
		if(task_flag!=0)
		{
			if(task_flag==1)	//��ǰΪ����1
			{
				if(Pulse2>1900)
				{
					task_finish_flag=1;	//������ɱ�־λ1
					LED_on();
					Beep_on();
					time_enable=1;
				}
			}
			
			else if(task_flag==2)	//��ǰΪ����2
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
					Pulse2=Pulse4=0;	//�ۼ�·������
					
					Target_Speed2=14;
					Target_Speed4=10;
					bar++;
				}
				if(bar==5&&Pulse2>500)	//turn right rectify length
				{
					Place_compensate_Enable=1;
					track_flag=0;
					Pulse2=Pulse4=0;	//�ۼ�·������
					
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
			Pwm_Out2=Pwm_Out4=0;	//װ���ٶ�����
			Pulse2=Pulse4=0;	//�ۼ�·������
			task_finish_flag=0;
			task_flag=0;
			target_infty_loop=0;
			bar=0;
		}
/**********************************************************************************************/	
		
/**********************************************���Ƴ���****************************************/
		if(task_flag!=0)	
		{
			if(Place_compensate_Enable==1)	//ֱ�߲���ʹ��
			{
				Place_difference_compensate=Place_difference_k*(Pulse2-Pulse4);	//ֱ�߲�ֵ����(���Ը��������Ǳջ�����)
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
		
		Load(Pwm_Out2,Pwm_Out4);	//װ�غ���
		
}
/***********************************************************************************************/
void GROUP1_IRQHandler(void)//Group1���жϷ�����
{	
/***************************************************************************************
			����������
****************************************************************************************/
uint32_t gpioB_0 = DL_GPIO_getEnabledInterruptStatus(GPIOB,DL_GPIO_PIN_18);
uint32_t gpioB_1 = DL_GPIO_getEnabledInterruptStatus(GPIOB,DL_GPIO_PIN_20);
//������1
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
	
//������2
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
�����ٶ�λ��ʽPID������
��ڲ���:����ֵ��Ŀ��ֵ
�������������PWM��
*************************/
int Speed_PID_L (int Target,int FeedBack )
{ 	
	int Pwm_Out;
	
	float SpeedL_err;
	
	static float SpeedL_Last_err,SpeedL_Sum;
	
//	if(flag_speed==1) {SpeedL_Sum=0;}	//��������
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
�����ٶ�λ��ʽPID������
��ڲ���:����ֵ��Ŀ��ֵ
�������������PWM��
*************************/
int Speed_PID_R (int Target,int FeedBack )
{ 	
	int Pwm_Out;
	
	float SpeedR_err;
	
	static float SpeedR_Last_err,SppedR_Sum;
	
//	if(flag_speed==1) {SppedR_Sum=0; flag_speed=0;}	//��������
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






