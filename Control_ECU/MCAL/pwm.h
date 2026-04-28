#ifndef PWM_H_
#define PWM_H_

/*----------------------------------------------INCLUDES----------------------------------------------*/

#include "std_types.h"
#include "common_macros.h"
#include <avr/io.h>

/*------------------------------------------------END-------------------------------------------------*/

/*--------------------------------------------Definitions---------------------------------------------*/

#ifndef F_CPU
#define F_CPU 16000000UL  // 16 MHz
#endif

#define SET_TIMER0_DC(DC) ( (DC > 100) ? (OCR0 = 255) : (OCR0 = ((DC * 255) / 100)) )

/*------------------------------------------------END-------------------------------------------------*/

/*-----------------------------------------Types Declaration------------------------------------------*/

typedef enum {
	TIMER0_PRESCALER_1, TIMER0_PRESCALER_8, TIMER0_PRESCALER_64, TIMER0_PRESCALER_256, TIMER0_PRESCALER_1024
}TIMER0_PRESCALER;

typedef enum {
	FAST_PWM, PHASE_PWM
}PWM_Mode ;

typedef enum {
	NON_INVERTING, INVERTING
}PWM_OutputMode ;

/*------------------------------------------------END-------------------------------------------------*/

/*--------------------------------------Extern Global Variables---------------------------------------*/ /*END*/

/*---------------------------------------Functions Like Macros----------------------------------------*/

static inline void Timer0_Reset(void)
{
	TCCR0 = 0;
	OCR0 = 0;
}

static inline void Timer0_EnableFastPWM(void)
{
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
}

static inline void Timer0_EnablePhaseCorrectPWM(void)
{
	SET_BIT(TCCR0, WGM00);
}

static inline void Timer0_SetNonInverting(void)
{
	SET_BIT(TCCR0, COM01);
}

static inline void Timer0_SetInverting(void)
{
	SET_BIT(TCCR0, COM01);
	SET_BIT(TCCR0, COM00);
}

static inline void Timer0_SetPrescaler_1(void)
{
	SET_BIT(TCCR0, CS00);					//zawad clear lal 3 we 5alas ya 3am
}

static inline void Timer0_SetPrescaler_8(void)
{
	SET_BIT(TCCR0, CS01);
}

static inline void Timer0_SetPrescaler_64(void)
{
	SET_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS00);
}

static inline void Timer0_SetPrescaler_256(void)
{
	SET_BIT(TCCR0, CS02);
}

static inline void Timer0_SetPrescaler_1024(void)
{
	SET_BIT(TCCR0, CS02);
	SET_BIT(TCCR0, CS00);
}


/*------------------------------------------------END-------------------------------------------------*/


/*----------------------------------------Functions Prototypes----------------------------------------*/

void PWM_Timer0_INIT(TIMER0_PRESCALER PSC, PWM_Mode mode, PWM_OutputMode output) ;

void PWM_Timer0_Stop() ;

void PWM_Timer0_SetDuty(uint8 DC) ;





#endif /* PWM_H_ */
