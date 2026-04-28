#include "motor.h"
#include "pwm.h"


void DcMotor_Init()
{
	PWM_Timer0_INIT(TIMER0_PRESCALER_64, FAST_PWM, NON_INVERTING) ;
	GPIO_setupPinDirection(MOTOR_IN1_PORT, MOTOR_IN1_PIN, PIN_OUTPUT) ;
	GPIO_setupPinDirection(MOTOR_IN2_PORT, MOTOR_IN2_PIN, PIN_OUTPUT) ;
	GPIO_setupPinDirection(MOTOR_ENABLE1_PORT, MOTOR_ENABLE1_PIN, PIN_OUTPUT) ;
}


void DcMotor_Rotate(MotorState state, uint8 DC)
{
	if(DC > 100)
		DC = 100 ;
	switch(state)
	{
		case CCW :
			GPIO_writePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, LOGIC_HIGH) ;
			GPIO_writePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, LOGIC_LOW) ;
			PWM_Timer0_SetDuty(DC) ;
			break ;
		case ACCW :
			GPIO_writePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, LOGIC_LOW) ;
			GPIO_writePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, LOGIC_HIGH) ;
			PWM_Timer0_SetDuty(DC) ;
			break ;
		case STOP :
			GPIO_writePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, LOGIC_LOW) ;
			GPIO_writePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, LOGIC_LOW) ;
			PWM_Timer0_SetDuty(0) ;
			break ;
	}
}
