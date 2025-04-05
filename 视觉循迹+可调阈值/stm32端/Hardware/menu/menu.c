#include "OLED.h"
#include "Key.h"
#include "menu.h"
#include "usart.h"
/*************************************************/
int mode=0;	//记录模式(手动模式，自动模式)
int Key_Num=0;
int flag=0;
/*************************************************/


/*************************************************
			其他参数
*************************************************/
extern u8 yuzhi_flag;
extern int yuzhi[6];
/*********************************************
                  菜单开始界面
********************************************/
int Menu_Start(void)
{
	int menu_select=1;	//记录选择
	mode=0; //改变模式
	
	OLED_ShowString(1,2,"Basic"); //基础部分
	OLED_ShowString(2,2,"Advance");	//发挥部分
	while(1)
	{	Key_Num=Key_GetNum();
		if(Key_Num==1)	//下一项
		{
			menu_select++;
			if(menu_select==3) menu_select=1;	//光标移动到最后一行的时候自动回到第一行
		}	

		if(Key_Num==2)	//确认按键
		{
			OLED_Clear();	//进入子级菜单前清屏
			return menu_select;
		}
		switch(menu_select)
		{
			case 1:
			{
				OLED_ShowChar(1,1,'>');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,' ');
			}break;
			
			case 2:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,'>');
				OLED_ShowChar(3,1,' ');
			}break;
		}
	}
}
/*********************************************
                  基础部分菜单
********************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      int Menu_Basic(void)
{
	int menu_select=1;
//	int mode=0;
	
	OLED_ShowString(1,2,"Basic.1"); 	
	OLED_ShowString(2,2,"Basic.2");	
	OLED_ShowString(3,2,"Basic.3"); 
	OLED_ShowString(4,2,"Basic.4");	
	
	while(1)
	{
		Key_Num=Key_GetNum();
		if(Key_Num==1)
		{
			menu_select++;
			if(menu_select==5) menu_select=1;
		}
		
		if(Key_Num==2)
		{
			OLED_Clear();
			if(menu_select==1) Menu_Basic_1();	//进入子菜单
			
			Key_Num=0;	//需要把按键清零，否则会直接退回到一级菜单
			
//			if(menu_select==2) Menu_Basic_2();
//			if(menu_select==3) Menu_Basic_3();
//			if(menu_select==4) Menu_Basic_4();
			
			OLED_ShowString(1,2,"Basic.1"); 	//再次显示菜单
			OLED_ShowString(2,2,"Basic.2");	
			OLED_ShowString(3,2,"Basic.3"); 
			OLED_ShowString(4,2,"Basic.4");	

		}
		
		if(Key_Num==4)
		{
			OLED_Clear();	//退出菜单
			
			return 0;
		}
		
		switch(menu_select) //光标移动
		{
			case 1:
			{
				OLED_ShowChar(1,1,'>');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			}break;
			
			case 2:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,'>');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			}break;
			case 3:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,'>');
				OLED_ShowChar(4,1,' ');
			}break;
			
			case 4:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,'>');
			}break;
		}
	}
	
}

/*********************************************
                  基础任务1
********************************************/
int Menu_Basic_1(void)
{
	int menu_select=1;
//	int mode;
	
	OLED_ShowString(1,2,"Auto_SetThr");
	OLED_ShowString(2,2,"Mutual_SetThr");
	while(1)
	{
		Key_Num=Key_GetNum();
		
		if(Key_Num==1)
		{
			menu_select++;	
			if(menu_select==3) menu_select=1;
		}
		
		if(Key_Num==2)
		{
			if(menu_select==1) 	usart1_SendByte('o');
			if(menu_select==2)	Threshold_Adjustion();	//进入手动阈值调整模式
			
			//重新显示菜单
			OLED_ShowString(1,2,"Auto_SetThr");
			OLED_ShowString(2,2,"Mutual_SetThr");
		}
		if(Key_Num==4)                                         
		{
			OLED_Clear();	//退出菜单
			return 0;
		}
		
		switch(menu_select) //光标移动
		{
			case 1:
			{
				OLED_ShowChar(1,1,'>');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			}break;
			
			case 2:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,'>');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			}break;
		}
	}

}
int Threshold_Adjustion(void)
{
	int menu_select=1;
	yuzhi_flag=1;	//进入阈值调试模式

	usart1_SendByte('a');	//发送使能信号
	
	OLED_Clear();
	OLED_ShowString(1,2,"L_min:"); 
	OLED_ShowString(2,2,"L_max:");
	OLED_ShowString(3,2,"A_min:");
	OLED_ShowString(4,2,"A_max:");
	
	while(1)
	{
		Key_Num=Key_GetNum();
		if(Key_Num==1)
		{
			menu_select++;
			if(menu_select==5)	//翻页
			{
				OLED_Clear();
				OLED_ShowString(1,2,"B_min:"); 
				OLED_ShowString(2,2,"B_max:");
			}
			if(menu_select==7) 
			{	
				OLED_Clear();
				menu_select=1;
				OLED_Clear();
				OLED_ShowString(1,2,"L_min:"); 	//重新显示页面
				OLED_ShowString(2,2,"L_max:");
				OLED_ShowString(3,2,"A_min:");
				OLED_ShowString(4,2,"A_max:");
			}
		}
		
		if(Key_Num==2)
		{
			if(menu_select==1) usart1_SendByte('c');
			if(menu_select==2) usart1_SendByte('d');
			if(menu_select==3) usart1_SendByte('e');
			if(menu_select==4) usart1_SendByte('f');
			if(menu_select==5) usart1_SendByte('g');
			if(menu_select==6) usart1_SendByte('h');
		}
		
		if(Key_Num==3)
		{
			if(menu_select==1) usart1_SendByte('i');
			if(menu_select==2) usart1_SendByte('j');
			if(menu_select==3) usart1_SendByte('k');
			if(menu_select==4) usart1_SendByte('l');
			if(menu_select==5) usart1_SendByte('m');
			if(menu_select==6) usart1_SendByte('n');
		}
		
		if(Key_Num==4)
		{
			OLED_Clear();
			
			yuzhi_flag=0;	//退出阈值调试模式
			
			usart1_SendByte('b');	//发送失能信号
	
			return 0;
		}
		
		if(menu_select<=4)
		{
			OLED_ShowSignedNum(1,10,yuzhi[0],3);
			OLED_ShowSignedNum(2,10,yuzhi[1],3);
			OLED_ShowSignedNum(3,10,yuzhi[2],3);
			OLED_ShowSignedNum(4,10,yuzhi[3],3);
		}
		if(menu_select>4)
		{
			OLED_ShowSignedNum(1,10,yuzhi[4],3);
			OLED_ShowSignedNum(2,10,yuzhi[5],3);
		}

		switch(menu_select) //光标移动
		{
			case 1:
			{
				OLED_ShowChar(1,1,'>');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			}break;
			
			case 2:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,'>');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			}break;
			case 3:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,'>');
				OLED_ShowChar(4,1,' ');
			}break;
			
			case 4:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,'>');
			}break;
			case 5:
			{
				OLED_ShowChar(1,1,'>');
				OLED_ShowChar(2,1,' ');
			}break;
			
			case 6:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,'>');
			}break;
		}
		
	}
}
