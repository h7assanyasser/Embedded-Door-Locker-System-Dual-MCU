#include "wakeup.h"
#include "uart.h"
#include "sleepmode.h"

void sleepTill_StartCMD()
{
	ENABLE_UART_INTERRUPT() ;
	enterIdleSleep() ;
	DISABLE_UART_INTERRUPT() ;
}



