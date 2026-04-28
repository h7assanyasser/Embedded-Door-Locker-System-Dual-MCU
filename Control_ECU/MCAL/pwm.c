#include "pwm.h"

void PWM_Timer0_INIT(TIMER0_PRESCALER PSC, PWM_Mode mode, PWM_OutputMode output)
{
	Timer0_Reset() ;
	if(mode == FAST_PWM)
	{
		Timer0_EnableFastPWM() ;
	}
	else
	{
		Timer0_EnablePhaseCorrectPWM() ;
	}
	if(output == NON_INVERTING)
	{
		Timer0_SetNonInverting() ;
	}
	else
	{
		Timer0_SetInverting() ;
	}
	switch (PSC)
	{
		case TIMER0_PRESCALER_1 :
			Timer0_SetPrescaler_1() ;
			break ;
		case TIMER0_PRESCALER_8 :
			Timer0_SetPrescaler_8() ;
			break ;
		case TIMER0_PRESCALER_64 :
			Timer0_SetPrescaler_64() ;
			break ;
		case TIMER0_PRESCALER_256 :
			Timer0_SetPrescaler_256() ;
			break ;
		case TIMER0_PRESCALER_1024 :
			Timer0_SetPrescaler_1024() ;
			break ;
	}
	PWM_Timer0_SetDuty(0) ;
}

void PWM_Timer0_Stop()
{
	Timer0_Reset() ;
}


void PWM_Timer0_SetDuty(uint8 DC)
{
	SET_TIMER0_DC(DC) ;
}




