#include "gpio.h"
#include "sleepmode.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */

void enterIdleSleep()
{
	// Select Idle Mode: SM1=0, SM0=0
	CLEAR_BIT(MCUCR, SM0);
	CLEAR_BIT(MCUCR, SM1);

	// Enable Sleep
	SET_BIT(MCUCR, SE);

	// Sleep
	SLEEP_UNTIL_WAKEN() ;

	// Clear SE bit after waking up
	CLEAR_BIT(MCUCR, SE);

}


