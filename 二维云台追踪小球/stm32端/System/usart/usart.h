#ifndef __usart1_H
#define __usart1_H

#include <stdio.h>

void usart1_Init(u32 Baud);
void usart1_SendByte(uint8_t Byte);
void usart1_SendArray(uint8_t *Array, uint16_t Length);
void usart1_SendString(char *String);
void usart1_SendNumber(uint32_t Number, uint8_t Length);
void usart1_Printf(char *format, ...);

void usart1_SendPacket(u8 *Array,u8 Length);	//发送一个数据包
//uint8_t usart1_GetRxFlag(void);

#endif
