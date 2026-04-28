#include "external_eeprom.h"
#include "buzzer.h"
#include "motor.h"
#include "pir.h"
#include "communication.h"
#include "alerttiming.h"
#include "wakeup.h"
#include "avr/io.h" 												//To use the SREG register to enable disable Global interrupt


#define F_CPU 8000000UL
#include <util/delay.h>

uint8 commandCRL = ACCESS_GRANTED ;
uint8 pass1[] = {'F','F','F','F','F'} ;
uint8 pass2[] = {'T','T','T','T','T'} ;								//Used to compare passwords

void sys_init()
{
	SREG |= (1 << 7) ;
	EEPROM_init() ;
	Buzzer_init() ;
	DcMotor_Init() ;
	PIR_init() ;
	communication_init() ;
}


void receivePass1()													//Store first try here
{
	for(uint8 i = 0 ; i < 5 ; i++)
	{
		pass1[i] = receive_Number() ;
		if(pass1[i] == ERROR_BYTE)									//Handling miss communication
		{
			DcMotor_Rotate(STOP,0) ;
			Buzzer_on() ;
			while(TRUE) ;
		}
	}
}

void receivePass2()													//Store second try here
{
	for(uint8 i = 0 ; i < 5 ; i++)
	{
		pass2[i] = receive_Number() ;
		if(pass2[i] == ERROR_BYTE)									//Handling miss communication
		{
			DcMotor_Rotate(STOP,0) ;
			Buzzer_on() ;
			while(TRUE) ;
		}
	}
}

boolean passwordsMatch()
{
	for(uint8 i = 0 ; i < 5 ; i++)
	{
		if(pass1[i] != pass2[i])
			return FALSE ;
	}
	return TRUE ;
}

void store_newPassword()
{
	for(uint8 i = 0 ; i < 5 ; i++)
	{
		EEPROM_writeByte(0x0311 + i, pass2[i]) ;
	}
}

boolean passwordCorrect()
{
	for(uint8 i = 0 ; i < 5 ; i++)
	{
		EEPROM_readByte(0x0311 + i, &(pass2[i])) ;
	}
	for(uint8 i = 0 ; i < 5 ; i++)
	{
		if(pass1[i] != pass2[i])
			return FALSE ;
	}
	return TRUE ;
}

void alertMode()
{
	Buzzer_on() ;
	startDoorAlertTimer() ;
	while(!passedAlertTime) ;
	Buzzer_off() ;
	send_CMD(ACCESS_GRANTED) ;
}


void unlockDoor()
{
	for(uint8 i = 1 ; i < 4 ; i++)
	{
		receivePass1() ;
		if(passwordCorrect())
		{
			send_CMD(ACCESS_GRANTED) ;
			break ;
		}
		else if(i == 3)												//I tried the password 3 times, i enter alert mode and infrom HMI
		{
			send_CMD(ALERT_MODE) ;
			alertMode() ;
			return ;
		}
		else
			send_CMD(ACCESS_DENIED) ;
	}

	DcMotor_Rotate(CCW,100) ;
	startDoorTiming() ;
	while(!passedAlertTime) ;										//To not rely only on PIR sensor wait till complete open
	DcMotor_Rotate(STOP,0) ;
	while(PIR_read()) ;
	send_CMD(LOCKING_DOOR) ;

	DcMotor_Rotate(ACCW,100) ;
	startDoorTiming() ;
	while(!passedAlertTime) ;
	DcMotor_Rotate(STOP,0) ;

	send_CMD(ACCESS_GRANTED) ;
}

void changePassword()
{
	for(uint8 i = 1 ; i < 4 ; i++)
	{
		receivePass1() ;
		if(passwordCorrect())
		{
			send_CMD(ACCESS_GRANTED) ;
			break ;
		}
		else if(i == 3)												//I tried the password 3 times, i enter alert mode and infrom HMI
		{
			send_CMD(ALERT_MODE) ;
			alertMode() ;
			return ;
		}
		else
			send_CMD(ACCESS_DENIED) ;
	}

	while(TRUE)
	{
		receivePass1() ;
		receivePass2() ;
		if(passwordsMatch())
		{
			send_CMD(ACCESS_GRANTED) ;
			store_newPassword() ;
			break ;
		}
		else
			send_CMD(ACCESS_DENIED) ;
	}
}

void setPassword()
{
	while(TRUE)
	{
		receivePass1() ;
		receivePass2() ;
		if(passwordsMatch())
		{
			send_CMD(ACCESS_GRANTED) ;
			store_newPassword() ;
			break ;
		}
		else
			send_CMD(ACCESS_DENIED) ;
	}
}

int main(void)
{
	sys_init() ;
	setPassword() ;
	while(1)
	{
		sleepTill_StartCMD() ;
		commandCRL = receive_CMD() ;
		if(commandCRL == UNLOCK_DOOR)
			unlockDoor() ;
		else if(commandCRL == ERROR_BYTE)									//Handling miss communication
		{
			DcMotor_Rotate(STOP,0) ;
			Buzzer_on() ;
			while(TRUE) ;
		}
		else
			changePassword() ;
	}
}


