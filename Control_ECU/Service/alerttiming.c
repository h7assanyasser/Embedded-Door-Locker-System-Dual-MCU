#include "alerttiming.h"
#include "timer.h"

/*This driver just to perform the LCD write clear operation in time*/

volatile boolean passedAlertTime = FALSE ;

static uint8 g_counter = 0 ;

void startDoorAlertTimer()
{
	Timer_ConfigType Timing = {0, 46875, TIMER1, F_CPU_1024, COMPARE_MODE} ;		//6 seconds each interrupt
	Timer_init(&Timing) ;
	Timer_setCallBack(AlertTimingHandler, TIMER1) ;
	passedAlertTime = FALSE ;
}

void startDoorTiming()
{
	Timer_ConfigType Timing = {0, 58593, TIMER1, F_CPU_1024, COMPARE_MODE} ;		//7.5 seconds each interrupt
	Timer_init(&Timing) ;
	Timer_setCallBack(doorTimeHandler, TIMER1) ;
	passedAlertTime = FALSE ;
}

void doorTimeHandler()
{
	g_counter++ ;
	if(g_counter == 2)
	{
		passedAlertTime = TRUE ;
		g_counter = 0 ;
		Timer_deInit(TIMER1) ;
	}
}

void AlertTimingHandler()
{
	g_counter++ ;
	if(g_counter == 6)
	{
		Timer_deInit(TIMER1) ;
		passedAlertTime = TRUE ;
		g_counter = 0 ;
	}
}

