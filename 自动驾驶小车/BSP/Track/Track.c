#include "board.h"
#include "Track.h"
//�ٶ�Ӽ����߼��жϣ�Ӧ�û����˿��
//extern int Place_compensate_Enable;	//��¼��ǰ���ܣ�0������ֱ�߲�����1������
extern int Target_Speed2,Target_Speed4;	//Ŀ���ٶ�
void Track_Enable(void)
{
	//��ȡѭ��
	int L2=DL_GPIO_readPins(Track_L2_PORT,Track_L2_PIN);
	int L1=DL_GPIO_readPins(Track_L1_PORT,Track_L1_PIN);
	int M=DL_GPIO_readPins(Track_M_PORT,Track_M_PIN);
	int R1=DL_GPIO_readPins(Track_R1_PORT,Track_R1_PIN);
	int R2=DL_GPIO_readPins(Track_R2_PORT,Track_R2_PIN);
	
	if(L2==0 && L1>0 && M==0 && R1==0 && R2==0)	//ƫ��
	{
		Target_Speed4=14;
		Target_Speed2=10;
	}
		
	else if(L2==0 && L1==0 && M==0 && R1>0 && R2==0)	//ƫ��
	{
		Target_Speed4=10;
		Target_Speed2=14;
	}
	
	else if(L2>0 && L1==0 && M==0 && R1==0 && R2==0)	//�ұ�ƫ����
	{
		Target_Speed4=16;
		Target_Speed2=4;
	}
	
	else if(L2==0 && L1==0 && M==0 && R1==0 && R2>0)	//���ƫ����
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