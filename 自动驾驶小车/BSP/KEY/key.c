#include "board.h"
#include "key.h"
uint8_t Key_GetNum(void)//高电平时按键按下
{
	uint8_t KeyNum = 0;	//没有按键按下时返回值为0
	if (DL_GPIO_readPins(KEY_PORT, KEY_PIN_15_PIN) > 0 )
	{
		delay_ms(20);
		while (DL_GPIO_readPins(KEY_PORT, KEY_PIN_15_PIN) > 0 );
		delay_ms(20);
		KeyNum = 1;
	}
	if (DL_GPIO_readPins(KEY_PORT, KEY_PIN_16_PIN) > 0 )
	{
		delay_ms(20);
		while (DL_GPIO_readPins(KEY_PORT, KEY_PIN_16_PIN) > 0 );
		delay_ms(20);
		KeyNum = 2;
	}
	if (DL_GPIO_readPins(KEY_PORT, KEY_PIN_17_PIN) > 0 )
	{
		delay_ms(20);
		while (DL_GPIO_readPins(KEY_PORT, KEY_PIN_17_PIN) > 0 );
		delay_ms(20);
		KeyNum = 3;
	}
	if (DL_GPIO_readPins(KEY_PORT, KEY_PIN_18_PIN) > 0 )
	{
		delay_ms(20);
		while (DL_GPIO_readPins(KEY_PORT, KEY_PIN_18_PIN) > 0 );
		delay_ms(20);
		KeyNum = 4;
	}
	return KeyNum;
}