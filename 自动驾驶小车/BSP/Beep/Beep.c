#include "board.h"
#include "Beep.h"

void Beep_on()
{
	DL_GPIO_clearPins(Beep_PORT,Beep_PIN_2_PIN);//����͵�ƽ
}
void Beep_off()
{
	DL_GPIO_setPins(Beep_PORT,Beep_PIN_2_PIN);  //����ߵ�ƽ
}        
