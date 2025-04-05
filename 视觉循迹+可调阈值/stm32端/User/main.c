#include "sys.h"
#include "OLED.h"
#include "Key.h"
#include "menu.h"
/*******************************************
			���ڽ��յ����ݰ�
********************************************/
int usart1_RxPacket[10];

/*******************************************
				�Ӿ�����
********************************************/
int Track[3]={0,0,0};
u8 yuzhi_flag=0;
int yuzhi[6];

int main(void)
{	
	int Menu_Select;
	
	Key_Init();
	
	OLED_Init();
	
	usart1_Init(115200);

	while(1)
	{	
		Menu_Select=Menu_Start();
		if(Menu_Select==1) Menu_Basic();              //����������ֵĲ˵� 
		//if(Menu_Select==2) Menu_Advanced();    
	}
		
}	

void USART1_IRQHandler(void)
{
	static int i=0;	//����һ���±�����������Ǿ�̬�ķ���ÿ�ν����жϺ���i���ᱻ���¶���
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		if(yuzhi_flag!=1)	//����ֵ����ģʽ
		{
			usart1_RxPacket[i++] = USART_ReceiveData(USART1);
			
			if(usart1_RxPacket[0]!=0xa3) i=0;	//�ж�֡ͷ
		
			if((i==2&&usart1_RxPacket[1]!=0xb3)) i=0;
			
			if(i==4)	//�������
			{
				if(usart1_RxPacket[3]==0xc3)	//�ж�֡β
				{
					/*******************************************
										��������
					********************************************/
					for(int j=0;j<3;j++)
					{
						Track[j]=usart1_RxPacket[2]%2;
						usart1_RxPacket[2]/=2;
					}
				}
				i=0; //�������
			}
		}
		
		if(yuzhi_flag==1)	//��ֵ����ģʽ
		{
			usart1_RxPacket[i++] = USART_ReceiveData(USART1);
			
			if(usart1_RxPacket[0]!=0xa3) i=0;	//�ж�֡ͷ
		
			if((i==2&&usart1_RxPacket[1]!=0xb3)) i=0;
			
			if(i==9)	//�������
			{
				if(usart1_RxPacket[8]==0xc3)	//�ж�֡β
				{
					/*******************************************
										��������
					********************************************/
					for(int j=0;j<6;j++)
					{
						yuzhi[j]=usart1_RxPacket[2+j];
					}
				}
				i=0; //�������
			}
		}
		
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//����жϱ�־λ
	
}

