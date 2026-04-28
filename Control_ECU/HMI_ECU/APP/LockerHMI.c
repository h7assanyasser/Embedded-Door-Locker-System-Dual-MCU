#include "lcd.h"
#include "lcddisplay.h"
#include "keypad.h"
#include "communication.h"
#include "avr/io.h" 												//To use the SREG register to enable disable Global interrupt

#define F_CPU 8000000UL
#include <util/delay.h>

uint8 commandCRL = ACCESS_GRANTED ;
uint8 pass[] = {'F','F','F','F','F','E'} ;							//Extra one for enter button

void sys_init()
{
	SREG |= (1 << 7) ;
	LCD_init() ;
	communication_init() ;
	LCD_displayString("Door Lock System") ;
	_delay_ms(1000) ;
	LCD_clearScreen() ;
}

void getPass()														//No display here to have it general function
{
	LCD_moveCursor(1,7) ;
	for(sint8 i = 0 ; i < 6 ; i++)									//We loop more than 5 so we keep checking for delete button
	{
		pass[i] = KEYPAD_getPressedKey() ;
		if(pass[i] == 'E' && i == 5)
		{
			break ;
		}															//12345678
		else if(pass[i] == 'D' && i > 0)							//pass: *
		{
			LCD_moveCursor(1,7+i-1) ;
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,7+i-1) ;
			i -= 2 ;
		}
		else if(pass[i] > 9 || pass[i] < 0 || pass[i] == 'D')		//If not numbers pass not counted
		{
			i-- ;
		}
		else if(i != 5)
		{
			LCD_displayCharacter('*');
		}
		else														//I pressed another number and i already entered five
		{
			i = 4 ;
		}
	}
}

void sendPass()
{
	getPass() ;
	for(uint8 i = 0 ; i < 5 ; i++)
	{
		send_Number(pass[i]) ;
	}
}

void receivePass()													//Won't need it here but write it to take to the other one
{
	for(uint8 i = 0 ; i < 5 ; i++)
	{
		pass[i] = receive_Number(pass[i]) ;
		if(pass[i] == ERROR_BYTE)									//Handling miss communication
		{
			LCD_clearScreen() ;
			LCD_displayString(" Commun. ERROR ") ;
			LCD_moveCursor(1,0) ;
			LCD_displayString(" check wires!! ") ;
			while(TRUE) ;
		}
	}
}

void alertMode()
{
	LCD_clearScreen() ;
	LCD_displayString("  System Locked") ;
	LCD_moveCursor(1,0) ;
	LCD_displayString("Wait for 1 min ") ;
	commandCRL = receive_CMD() ;									//I should receive here ACCESS_GRANTED so we can return to main menu
	if(commandCRL == ERROR_BYTE)									//Handling miss communication
	{
		LCD_clearScreen() ;
		LCD_displayString(" Commun. ERROR ") ;
		LCD_moveCursor(1,0) ;
		LCD_displayString(" check wires!! ") ;
		while(TRUE) ;
	}
}


void unlockDoor()
{
	send_CMD(UNLOCK_DOOR) ;											//So CRL knows to open door after checking password
	while(TRUE)														//Means i got ACCESS_DENIED still not reached alert mode
	{
		LCD_clearScreen() ;
		LCD_displayString("PLZ enter old") ;
		LCD_moveCursor(1,0) ;
		LCD_displayString("pass: ") ;

		sendPass() ;												/*****CRL Receive here then sends CMD*****/
		commandCRL = receive_CMD() ;
		if(commandCRL == ACCESS_GRANTED)
			break ;
		else if(commandCRL == ALERT_MODE)
		{
			alertMode() ;
			return ;												//I should not continue the function i return to main options
		}
		else if(commandCRL == ERROR_BYTE)							//Handling miss communication
		{
			LCD_clearScreen() ;
			LCD_displayString(" Commun. ERROR ") ;
			LCD_moveCursor(1,0) ;
			LCD_displayString(" check wires!! ") ;
			while(TRUE) ;
		}
	}

	LCD_startDoorStateTimer(CLOSED) ;
	commandCRL = receive_CMD() ;									/*****Here i receive LOCKING_DOOR*****/
	if(commandCRL == ERROR_BYTE)									//Handling miss communication
	{
		LCD_clearScreen() ;
		LCD_displayString(" Commun. ERROR ") ;
		LCD_moveCursor(1,0) ;
		LCD_displayString(" check wires!! ") ;
		while(TRUE) ;
	}

	LCD_startDoorStateTimer(OPENED) ;
	commandCRL = receive_CMD() ;
	if(commandCRL == ERROR_BYTE)									//Handling miss communication
	{
		LCD_clearScreen() ;
		LCD_displayString(" Commun. ERROR ") ;
		LCD_moveCursor(1,0) ;
		LCD_displayString(" check wires!! ") ;
		while(TRUE) ;
	}
}

void changePassword()
{
	send_CMD(NEW_PASSWORD) ;										//So CRL knows to change password after checking password
	while(TRUE)														//Means i got ACCESS_DENIED still not reached alert mode
	{
		LCD_clearScreen() ;
		LCD_displayString("PLZ enter old") ;
		LCD_moveCursor(1,0) ;
		LCD_displayString("pass: ") ;

		sendPass() ;												/*****CRL Receive here then sends CMD*****/
		commandCRL = receive_CMD() ;
		if(commandCRL == ACCESS_GRANTED)
			break ;
		else if(commandCRL == ALERT_MODE)
		{
			alertMode() ;
			return ;												//I should not continue the function i return to main options
		}
		else if(commandCRL == ERROR_BYTE)									//Handling miss communication
		{
			LCD_clearScreen() ;
			LCD_displayString(" Commun. ERROR ") ;
			LCD_moveCursor(1,0) ;
			LCD_displayString(" check wires!! ") ;
			while(TRUE) ;
		}
	}
	while(TRUE)
	{
		LCD_clearScreen() ;											//Sending First password
		LCD_displayString("PLZ enter pass:") ;
		LCD_moveCursor(1,0) ;
		sendPass() ;

		LCD_clearScreen() ;											//Sending second password, renter
		LCD_displayString("PLZ renter same") ;
		LCD_moveCursor(1,0) ;
		LCD_displayString("pass: ") ;
		sendPass() ;
		commandCRL = receive_CMD() ;
		if(commandCRL == ACCESS_GRANTED)							//Else means i i got ACCESS_DENIED so i keep looping
		{
			LCD_clearScreen() ;
			LCD_displayString("Password Changed!") ;
			_delay_ms(1000) ;
			break ;
		}
		else if(commandCRL == ERROR_BYTE)							//Handling miss communication
		{
			LCD_clearScreen() ;
			LCD_displayString(" Commun. ERROR ") ;
			LCD_moveCursor(1,0) ;
			LCD_displayString(" check wires!! ") ;
			while(TRUE) ;
		}
		else
		{
			LCD_clearScreen() ;
			LCD_displayString("Password mismatch") ;
			_delay_ms(1000) ;
		}
	}
}

void setPassword()
{
	while(TRUE)
	{
		LCD_clearScreen() ;											//Sending First password
		LCD_displayString("PLZ enter pass:") ;
		LCD_moveCursor(1,0) ;
		sendPass() ;

		LCD_clearScreen() ;											//Sending second password, renter
		LCD_displayString("PLZ renter same") ;
		LCD_moveCursor(1,0) ;
		LCD_displayString("pass: ") ;
		sendPass() ;
		commandCRL = receive_CMD() ;
		if(commandCRL == ACCESS_GRANTED)							//Else means i i got ACCESS_DENIED so i keep looping
		{
			LCD_clearScreen() ;
			LCD_displayString("Password Made!") ;
			_delay_ms(1000) ;
			break ;
		}
		else if(commandCRL == ERROR_BYTE)							//Handling miss communication
		{
			LCD_clearScreen() ;
			LCD_displayString(" Commun. ERROR ") ;
			LCD_moveCursor(1,0) ;
			LCD_displayString(" check wires!! ") ;
			while(TRUE) ;
		}
		else
		{
			LCD_clearScreen() ;
			LCD_displayString("Password mismatch") ;
			_delay_ms(1000) ;
		}
	}
}

int main(void)
{
	sys_init() ;
	setPassword() ;
	uint8 option = 0 ;

	while(1)
	{
		LCD_clearScreen() ;
		LCD_displayString("+ : OPEN DOOR") ;
		LCD_moveCursor(1,0) ;
		LCD_displayString("- : CHANGE PASS") ;

		while(TRUE)
		{
			option = KEYPAD_getPressedKey() ;
			if(option == '+' || option == '-')
				break ;
		}
		if(option == '+')
			unlockDoor() ;
		else
			changePassword() ;
	}
}


