#include "communication.h"
#include "uart.h"
#include "gpio.h"

void communication_init()
{
	UART_ConfigType UART = {UART_8_BIT, UART_PARITY_DISABLED, UART_ONE_STOP_BIT, UART_BAUD_9600} ;
	GPIO_setupPinDirection(UART_TXD_PORT_ID, UART_TXD_PIN_ID, PIN_OUTPUT) ;
	UART_init(&UART) ;
}

void send_CMD(uint8 command)
{
	UART_sendByte(command) ;
}

void send_Number(uint8 num)
{
	UART_sendByte(num) ;
}

boolean validate_Number(uint8 num)
{
	if (num >= 0 && num <= 9)
		return TRUE;
	else
		return FALSE;
}

uint8 receive_Number()
{
	uint8 num = UART_recieveByte();

	if (!validate_Number(num))
	{
		send_CMD(ERROR_BYTE) ;
		return ERROR_BYTE ;
	}
	return num;
}

boolean validate_CMD(uint8 cmd)									//If i receive anything other than our protocol then i return error
{																//Instead of UART error checking as we have fixedd protocol
	switch (cmd)
	{
		case START_BYTE:
		case ACCESS_GRANTED:
		case WRONG_RENTER:
		case ACCESS_DENIED:
		case ALERT_MODE:
		case UNLOCK_DOOR:
		case NEW_PASSWORD:
		case LOCKING_DOOR:
			return TRUE;
		default:
			return FALSE;
	}
}

uint8 receive_CMD()
{
	uint8 cmd = UART_recieveByte();

	if (!validate_CMD(cmd))
	{
		send_CMD(ERROR_BYTE) ;
		return (ERROR_BYTE) ;
	}
	return cmd ;
}
