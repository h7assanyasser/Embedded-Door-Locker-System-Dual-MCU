#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */


void GPIO_setupPinDirection(uint8 portNum, uint8 pinNum, GPIO_PinDirectionType direction)
{
	if(portNum >= NUM_OF_PORTS || pinNum >= NUM_OF_PINS_PER_PORT)
	{

	}
	else
	{
		switch (portNum)
		{
			case PORTA_ID :
				WRITE_BIT(DDRA,pinNum,direction)  ;
				break ;
			case PORTB_ID :
				WRITE_BIT(DDRB,pinNum,direction)  ;
				break ;
			case PORTC_ID :
				WRITE_BIT(DDRC,pinNum,direction)  ;
				break ;
			case PORTD_ID :
				WRITE_BIT(DDRD,pinNum,direction)  ;
				break ;
		}
	}
}


uint8 GPIO_readPin(uint8 portNum, uint8 pinNum)
{
	if(portNum >= NUM_OF_PORTS || pinNum >= NUM_OF_PINS_PER_PORT)
	{
		/* DO NOTHING better than returning -1 i think */
	}
	else
	{
		switch (portNum)
		{
			case PORTA_ID :
				return GET_BIT(PINA,pinNum)  ;
			case PORTB_ID :
				return GET_BIT(PINB,pinNum)  ;
			case PORTC_ID :
				return GET_BIT(PINC,pinNum)  ;
			case PORTD_ID :
				return GET_BIT(PIND,pinNum)  ;
		}
	}
	return LOGIC_LOW ;		/* Not in if to remove warning */
}


void GPIO_writePin(uint8 portNum, uint8 pinNum, LOGIC logic)
{
	if(portNum >= NUM_OF_PORTS || pinNum >= NUM_OF_PINS_PER_PORT)
	{
		/* DO NOTHING better than returning -1 i think */
	}
	else
	{
		switch (portNum)
		{
			case PORTA_ID :
				WRITE_BIT(PORTA,pinNum,logic)  ;
				break ;
			case PORTB_ID :
				WRITE_BIT(PORTB,pinNum,logic)  ;
				break ;
			case PORTC_ID :
				WRITE_BIT(PORTC,pinNum,logic)  ;
				break ;
			case PORTD_ID :
				WRITE_BIT(PORTD,pinNum,logic)  ;
				break ;
		}
	}
}

void GPIO_setupPortDirection(uint8 portNum, GPIO_PortDirectionType direction)				//Assuming compiler actually  gives warning if assign direction wrong
{
	if(portNum >= NUM_OF_PORTS)
	{

	}
	else
	{
		switch(portNum)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

void GPIO_writePort(uint8 portNum, GPIO_PortLevel value)
{
	if(portNum >= NUM_OF_PORTS)
	{

	}
	else
	{
		switch(portNum)
		{
		case PORTA_ID:
			PORTA = value;
			break ;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}



uint8 GPIO_readPort(uint8 portNum)
{
	if(portNum >= NUM_OF_PORTS)
	{
		/* DO NOTHING better than returning -1 i think */
	}
	else
	{
		switch (portNum)
		{
			case PORTA_ID :
				return PINA ;
			case PORTB_ID :
				return PINB ;
			case PORTC_ID :
				return PINC ;
			case PORTD_ID :
				return PIND ;
		}
	}
	return PORT_LOW ;		/* Not in if to remove warning */
}

