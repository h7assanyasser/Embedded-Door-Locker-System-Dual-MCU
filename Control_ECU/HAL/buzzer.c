#include "buzzer.h"



void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT) ;
	Buzzer_off() ;
}

void Buzzer_on()
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH) ;
}

void Buzzer_off()
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW) ;
}





