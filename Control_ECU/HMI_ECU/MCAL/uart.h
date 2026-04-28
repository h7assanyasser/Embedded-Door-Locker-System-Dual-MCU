#ifndef UART_H_
#define UART_H_

#include "std_types.h"


/*-----------------------------------------Types Declaration------------------------------------------*/

typedef enum {
    UART_5_BIT, UART_6_BIT, UART_7_BIT, UART_8_BIT
} UART_BitDataType;

typedef enum {
    UART_PARITY_DISABLED, UART_PARITY_EVEN = 2, UART_PARITY_ODD
} UART_ParityType;

typedef enum {
    UART_ONE_STOP_BIT, UART_TWO_STOP_BIT
} UART_StopBitType;

typedef enum {
    UART_BAUD_2400 = 2400,
    UART_BAUD_4800 = 4800,
    UART_BAUD_9600 = 9600,
    UART_BAUD_14400 = 14400,
    UART_BAUD_19200 = 19200,
    UART_BAUD_38400 = 38400,
    UART_BAUD_57600 = 57600,
    UART_BAUD_115200 = 115200
} UART_BaudRateType;

/* Configuration struct */
typedef struct {
    UART_BitDataType bit_data;
    UART_ParityType parity;
    UART_StopBitType stop_bit;
    UART_BaudRateType baud_rate;
} UART_ConfigType;

/*------------------------------------------------END-------------------------------------------------*/



/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
