#include "timer.h"
#include "lcd.h"
#include "lcddisplay.h"
										/*This driver just to perform the LCD write clear operation in time, service layer*/
static uint8 g_counter = 0 ;

void LCD_startDoorStateTimer(DOOR_STATE state)
{
	Timer_ConfigType Timing = {0, 58594, TIMER1, F_CPU_1024, COMPARE_MODE} ;
	Timer_init(&Timing) ;
	if(state == CLOSED)
	{
		Timer_setCallBack(LCD_displayOpeningTimed, TIMER1) ;
		LCD_clearScreen();
		LCD_displayString("  Door Unlocking");
		LCD_moveCursor(1,0);
		LCD_displayString("   Please wait");
	}
	else
	{
		Timer_setCallBack(LCD_displayclosingTimed, TIMER1) ;
		LCD_clearScreen();
		LCD_displayString("   Door locking");
	}
}

void LCD_displayOpeningTimed()
{
	g_counter++ ;
	if(g_counter == 2)
	{
		LCD_clearScreen();
		LCD_displayString("Wait for people");
		LCD_moveCursor(1,0);
		LCD_displayString("    to enter");
		g_counter = 0 ;
		Timer_deInit(TIMER1);
	}
}

void LCD_displayclosingTimed()
{
	g_counter++ ;
	if(g_counter == 2)
	{
		Timer_deInit(TIMER1);
		g_counter = 0 ;
	}
}



