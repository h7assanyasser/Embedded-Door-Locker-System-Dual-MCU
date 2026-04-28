#ifndef GPIO_H_
#define GPIO_H_

/*----------------------------------------------INCLUDES----------------------------------------------*/

#include "std_types.h"

/*------------------------------------------------END-------------------------------------------------*/


/*--------------------------------------------Definitions---------------------------------------------*/

#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3
#define OC0_PORT_ID PORTB_ID
#define ADC_CHANNEL0_PORT_ID PORTA_ID
#define ADC_CHANNEL1_PORT_ID PORTA_ID
#define UART_TXD_PORT_ID PORTD_ID


#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define OC0_PIN PIN3
#define ADC_CHANNEL0_PIN_ID PIN0
#define ADC_CHANNEL1_PIN_ID PIN1
#define UART_TXD_PIN_ID PIN1

/*------------------------------------------------END-------------------------------------------------*/

/*-----------------------------------------Types Declaration------------------------------------------*/

typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

typedef enum
{
	PORT_LOW,PORT_HIGH=0xFF
}GPIO_PortLevel;

/*------------------------------------------------END-------------------------------------------------*/


/*--------------------------------------Extern Global Variables---------------------------------------*/ /*END*/
/*---------------------------------------Functions Like Macros----------------------------------------*/ /*END*/


/*----------------------------------------Functions Prototypes----------------------------------------*/

void GPIO_setupPinDirection(uint8 portNum, uint8 pinNum, GPIO_PinDirectionType direction) ;

uint8 GPIO_readPin(uint8 portNum, uint8 pinNum) ;

void GPIO_writePin(uint8 portNum, uint8 pinNum, uint8 value) ;

void GPIO_setupPortDirection(uint8 portNum, GPIO_PortDirectionType direction) ;

uint8 GPIO_readPort(uint8 portNum) ;

void GPIO_writePort(uint8 portNum, uint8 value) ;

/*------------------------------------------------END-------------------------------------------------*/


#endif /* GPIO_H_ */
