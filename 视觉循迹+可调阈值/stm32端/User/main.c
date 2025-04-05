#include "sys.h"
#include "OLED.h"
#include "Key.h"
#include "menu.h"
/*******************************************
			串口接收的数据包
********************************************/
int usart1_RxPacket[10];

/*******************************************
				视觉数据
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
		if(Menu_Select==1) Menu_Basic();              //进入基础部分的菜单 
		//if(Menu_Select==2) Menu_Advanced();    
	}
		
}	

void USART1_IRQHandler(void)
{
	static int i=0;	//定义一个下标变量，必须是静态的否则每次进入中断函数i都会被重新定义
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		if(yuzhi_flag!=1)	//非阈值调试模式
		{
			usart1_RxPacket[i++] = USART_ReceiveData(USART1);
			
			if(usart1_RxPacket[0]!=0xa3) i=0;	//判断帧头
		
			if((i==2&&usart1_RxPacket[1]!=0xb3)) i=0;
			
			if(i==4)	//接收完毕
			{
				if(usart1_RxPacket[3]==0xc3)	//判断帧尾
				{
					/*******************************************
										更新数据
					********************************************/
					for(int j=0;j<3;j++)
					{
						Track[j]=usart1_RxPacket[2]%2;
						usart1_RxPacket[2]/=2;
					}
				}
				i=0; //清空数组
			}
		}
		
		if(yuzhi_flag==1)	//阈值调试模式
		{
			usart1_RxPacket[i++] = USART_ReceiveData(USART1);
			
			if(usart1_RxPacket[0]!=0xa3) i=0;	//判断帧头
		
			if((i==2&&usart1_RxPacket[1]!=0xb3)) i=0;
			
			if(i==9)	//接收完毕
			{
				if(usart1_RxPacket[8]==0xc3)	//判断帧尾
				{
					/*******************************************
										更新数据
					********************************************/
					for(int j=0;j<6;j++)
					{
						yuzhi[j]=usart1_RxPacket[2+j];
					}
				}
				i=0; //清空数组
			}
		}
		
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//清除中断标志位
	
}

