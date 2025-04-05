#include "board.h"
#include "Beep.h"

void Beep_on()
{
	DL_GPIO_clearPins(Beep_PORT,Beep_PIN_2_PIN);//输出低电平
}
void Beep_off()
{
	DL_GPIO_setPins(Beep_PORT,Beep_PIN_2_PIN);  //输出高电平
}        
