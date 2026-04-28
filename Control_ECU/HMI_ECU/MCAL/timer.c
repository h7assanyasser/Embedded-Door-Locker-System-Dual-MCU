#include "timer.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/interrupt.h>


static void (*g_timer0_callBackPtr)(void) = NULL_PTR;
static void (*g_timer1_callBackPtr)(void) = NULL_PTR;
static void (*g_timer2_callBackPtr)(void) = NULL_PTR;


void Timer_init2(const Timer_ConfigType * Config_Ptr)
{
	switch (Config_Ptr->timer_ID)
	{
		case TIMER0:
			TCCR0 = (Config_Ptr->timer_mode << WGM00) ;						/*Timer mode normal or compare*/
			TCNT0 = Config_Ptr->timer_InitialValue ;						/*Timer initial value*/
			TIMSK |= (1 << TOIE0) | (1 << OCIE0) ;							/*Enable interrupt normal and compare doesn't matter no need to do the check*/
			OCR0 = Config_Ptr->timer_compare_MatchValue ;					/*Timer compare value no need for mode check just do it*/
			TCCR0 |= (Config_Ptr->timer_clock << CS00) ;					/*Timer Frequency*/
			break ;

		case TIMER1:

			// Set Timer1 to CTC mode: WGM12 = 1
			TCCR1A = 0;
			TCCR1B = (1 << WGM12);  // CTC mode (TOP = OCR1A)

			// Set compare value for 2 seconds
			// 2s = 2 * 8,000,000 / 1024 = 15625
			OCR1A = 15625;

			// Set initial counter value
			TCNT1 = 0;

			// Enable Timer1 Compare A Match Interrupt
			TIMSK |= (1 << OCIE1A);

			// Set prescaler = 1024 → start timer
			TCCR1B |= (1 << CS12) | (1 << CS10);  // Clock = F_CPU/1024

			break ;

		case TIMER2:
			TCCR2 = (Config_Ptr->timer_mode << WGM20) ;					/*Timer mode normal or compare*/
			TCNT2 = Config_Ptr->timer_InitialValue ;						/*Timer initial value*/
			TIMSK |= (1 << TOIE2) | (1 << OCIE2) ;							/*Enable interrupt normal and compare doesn't matter no need to do the check*/
			OCR2 = Config_Ptr->timer_compare_MatchValue ;					/*Timer compare value no need for mode check just do it*/
			TCCR2 |= (Config_Ptr->timer_clock << CS20) ;					/*Timer Frequency*/
			break ;
	}
}

void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	switch (Config_Ptr->timer_ID)
	{
		case TIMER0:
			TCCR0 = (Config_Ptr->timer_mode << WGM00) ;						/*Timer mode normal or compare*/
			TCNT0 = Config_Ptr->timer_InitialValue ;						/*Timer initial value*/
			TIMSK |= (1 << TOIE0) | (1 << OCIE0) ;							/*Enable interrupt normal and compare doesn't matter no need to do the check*/
			OCR0 = Config_Ptr->timer_compare_MatchValue ;					/*Timer compare value no need for mode check just do it*/
			TCCR0 |= (Config_Ptr->timer_clock << CS00) ;					/*Timer Frequency*/
			break ;

		case TIMER1:
			if(Config_Ptr->timer_mode == COMPARE_MODE)
				TCCR1B = (1 << WGM12) ;										/*Timer compare mode*/

			TCNT1 = Config_Ptr->timer_InitialValue ;						/*Timer initial value, AVR handles H and L split*/

			TIMSK |= (1 << TOIE1) | (1 << OCIE1A) ;							/*Enable interrupt normal and compare doesn't matter no need to do the check*/
			OCR1A = Config_Ptr->timer_compare_MatchValue ;					/*Timer compare value no need for mode check just do it*/
			TCCR1B |= (Config_Ptr->timer_clock << CS10) ;					/*Timer Frequency*/

			break ;

		case TIMER2:
			TCCR2 = (Config_Ptr->timer_mode << WGM20) ;					/*Timer mode normal or compare*/
			TCNT2 = Config_Ptr->timer_InitialValue ;						/*Timer initial value*/
			TIMSK |= (1 << TOIE2) | (1 << OCIE2) ;							/*Enable interrupt normal and compare doesn't matter no need to do the check*/
			OCR2 = Config_Ptr->timer_compare_MatchValue ;					/*Timer compare value no need for mode check just do it*/
			TCCR2 |= (Config_Ptr->timer_clock << CS20) ;					/*Timer Frequency*/
			break ;
	}
}

void Timer_deInit(Timer_ID_Type timer_type)
{
	switch (timer_type)
	{
	case TIMER0:
		TCCR0 = 0;
		break ;
	case TIMER1:
		TCCR1A = 0;
		TCCR1B = 0 ;
		break ;
	case TIMER2:
		TCCR2 = 0;
		break ;
	}
}

void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID)
{
	switch (a_timer_ID)
	{
		case TIMER0:
			g_timer0_callBackPtr = a_ptr;
			break;
		case TIMER1:
			g_timer1_callBackPtr = a_ptr;
			break;
		case TIMER2:
			g_timer2_callBackPtr = a_ptr;
			break;
	}
}

ISR(TIMER0_OVF_vect)
{
	if(g_timer0_callBackPtr != NULL_PTR)
		(*g_timer0_callBackPtr)() ;
}

ISR(TIMER0_COMP_vect)
{
	if(g_timer0_callBackPtr != NULL_PTR)
		(*g_timer0_callBackPtr)() ;
}

ISR(TIMER1_OVF_vect)
{
	if(g_timer1_callBackPtr != NULL_PTR)
		(*g_timer1_callBackPtr)() ;
}

ISR(TIMER1_COMPA_vect)
{
	if(g_timer1_callBackPtr != NULL_PTR)
		(*g_timer1_callBackPtr)() ;
}

ISR(TIMER2_OVF_vect)
{
	if(g_timer2_callBackPtr != NULL_PTR)
		(*g_timer2_callBackPtr)() ;
}

ISR(TIMER2_COMP_vect)
{
	if(g_timer2_callBackPtr != NULL_PTR)
		(*g_timer2_callBackPtr)() ;
}

