#include "board.h"
#include "Track.h"
//再多加几组逻辑判断，应该会更加丝滑
//extern int Place_compensate_Enable;	//记录当前功能（0不开启直线补偿，1开启）
extern int Target_Speed2,Target_Speed4;	//目标速度
void Track_Enable(void)
{
	//读取循迹
	int L2=DL_GPIO_readPins(Track_L2_PORT,Track_L2_PIN);
	int L1=DL_GPIO_readPins(Track_L1_PORT,Track_L1_PIN);
	int M=DL_GPIO_readPins(Track_M_PORT,Track_M_PIN);
	int R1=DL_GPIO_readPins(Track_R1_PORT,Track_R1_PIN);
	int R2=DL_GPIO_readPins(Track_R2_PORT,Track_R2_PIN);
	
	if(L2==0 && L1>0 && M==0 && R1==0 && R2==0)	//偏右
	{
		Target_Speed4=14;
		Target_Speed2=10;
	}
		
	else if(L2==0 && L1==0 && M==0 && R1>0 && R2==0)	//偏左
	{
		Target_Speed4=10;
		Target_Speed2=14;
	}
	
	else if(L2>0 && L1==0 && M==0 && R1==0 && R2==0)	//右边偏飞了
	{
		Target_Speed4=16;
		Target_Speed2=4;
	}
	
	else if(L2==0 && L1==0 && M==0 && R1==0 && R2>0)	//左边偏飞了
	{
		Target_Speed4=4;
		Target_Speed2=16;
	}
	else
	{
		Target_Speed4=10;
		Target_Speed2=10;
	}
		
}