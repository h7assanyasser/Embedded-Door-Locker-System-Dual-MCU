#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */


void UART_init(const UART_ConfigType * Config_Ptr)
{
	/*Set Baud Rate */

	uint16 ubrr_value = 0;
	UCSRA = (1<<U2X);															/* U2X = 1 for double transmission speed */
	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);		/* Calculate the UBRR register value */
	UBRRH = ubrr_value>>8;														/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRL = ubrr_value;

	/*Enable Transmit and receive*/

	UCSRB = (1<<RXEN) | (1<<TXEN);

	/*Set frame bits*/

	UCSRC = (1<<URSEL) ;														/*URSEL must be one when writing the UCSRC*/

	UCSRC |= (Config_Ptr->parity<<UPM0) ;

	UCSRC |= (Config_Ptr->stop_bit<<USBS) ;

	UCSRC |= (Config_Ptr->bit_data<<UCSZ0) ;
}




/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;		
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
