#include "board.h"
#include "LED.h"

void LED_off()
{
	DL_GPIO_clearPins(LED1_PORT,LED1_PIN_21_PIN);//����͵�ƽ
}
void LED_on()
{
	DL_GPIO_setPins(LED1_PORT,LED1_PIN_21_PIN);  //����ߵ�ƽ
}        
