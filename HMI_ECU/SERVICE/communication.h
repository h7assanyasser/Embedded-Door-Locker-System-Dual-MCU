#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

/*----------------------------------------------INCLUDES----------------------------------------------*/

#include "std_types.h"

/*------------------------------------------------END-------------------------------------------------*/

/*--------------------------------------------Definitions---------------------------------------------*/

#define START_BYTE 0xAA
#define ACCESS_GRANTED 'A'
#define WRONG_RENTER 'R'
#define ACCESS_DENIED 'D'

#define ALERT_MODE 'M'
#define UNLOCK_DOOR 'U'
#define NEW_PASSWORD 'W'
#define LOCKING_DOOR 'L'
#define ERROR_BYTE 0xFF										/*didn't receive start byte or anything*/

#define CHECK_PASSWORD 'C'
#define SET_PASSWORD 'P'



/*------------------------------------------------END-------------------------------------------------*/

/*-----------------------------------------Types Declaration------------------------------------------*/

typedef enum{
	DOOR_OPEN, DOOR_CLOSE, PASSWORD_CHANGE
}CMD;

/*------------------------------------------------END-------------------------------------------------*/

/*--------------------------------------Extern Global Variables---------------------------------------*/ /*END*/

/*---------------------------------------Functions Like Macros----------------------------------------*/ /*END*/


/*----------------------------------------Functions Prototypes----------------------------------------*/

void communication_init() ;

void send_CMD(uint8 command) ;

void send_Number(uint8 num) ;

uint8 receive_Number() ;

uint8 receive_CMD() ;

/*------------------------------------------------END-------------------------------------------------*/




#endif /* COMMUNICATION_H_ */
