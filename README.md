# Embedded Door Locker System (Dual MCU)

## Overview
This project implements a secure smart door locking system using two microcontrollers communicating via UART. The system provides password-based authentication with EEPROM storage and integrates multiple peripherals for real-time operation.

## System Architecture
The system consists of two microcontrollers:

### HMI_ECU
- LCD display for user interaction
- Keypad for password input
- Sends commands via UART

### Control_ECU
- EEPROM for password storage
- Motor driver for door control
- PIR sensor for motion detection
- Buzzer for security alerts

## Features
- Password authentication with confirmation
- UART communication between ECUs
- EEPROM-based password storage
- Motorized door locking/unlocking
- PIR-based motion detection
- Buzzer alert for failed attempts
- Security lock after multiple incorrect tries

## Drivers Used
- GPIO
- UART
- I2C (EEPROM)
- Timer
- PWM (Motor control)
- LCD
- Keypad

## Technologies
- Embedded C
- ATmega32
- Layered architecture design
- Real-time embedded system design

## Author
Hassan Yasser
