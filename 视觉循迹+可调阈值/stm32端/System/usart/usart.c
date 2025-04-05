#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>


//uint8_t usart1_RxFlag;

void usart1_Init(u32 Baud)	//usart1���ڳ�ʼ��
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = Baud;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//�շ�ģʽ
	USART_InitStructure.USART_Parity = USART_Parity_No;	//��У��λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //һλֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//�ж�ʹ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}

void usart1_SendByte(uint8_t Byte)	//����һ���ַ�
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void usart1_SendArray(uint8_t *Array, uint16_t Length)	//����һ�����飨0x��ʽ���ͣ�
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		usart1_SendByte(Array[i]);
	}
}

void usart1_SendString(char *String)	//����һ���ַ�������
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		usart1_SendByte(String[i]);
	}
}

uint32_t usart1_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void usart1_SendNumber(uint32_t Number, uint8_t Length)	//����һ�����֣����͵���ʵ��char�����֣�
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		usart1_SendByte(Number / usart1_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)
{
	usart1_SendByte(ch);
	return ch;
}

void usart1_Printf(char *format, ...)	//Printf��ӡ����
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	usart1_SendString(String);
}

void usart1_SendPacket(u8 *Array,u8 Length)	//����һ�����ݰ�
{
	usart1_SendByte(0xFF);
	usart1_SendArray(Array,Length);
	usart1_SendByte(0xFE);
}

//void usart1_SendPacket(void)	//����һ�����ݰ�
//{
//	usart1_SendByte(0xFF);
//	usart1_SendArray(usart1_TxPacket, 4);
//	usart1_SendByte(0xFE);
//}

//uint8_t usart1_GetRxFlag(void)
//{
//	if (usart1_RxFlag == 1)
//	{
//		usart1_RxFlag = 0;
//		return 1;
//	}
//	return 0;
//}




