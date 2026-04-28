#include "pir.h"
#include "gpio.h"

void PIR_init()
{
	GPIO_setupPinDirection(PIR_PORT_ID, PIR_PIN, PIN_INPUT) ;
}

uint8 PIR_read()
{
	return GPIO_readPin(PIR_PORT_ID, PIR_PIN) ;
}
