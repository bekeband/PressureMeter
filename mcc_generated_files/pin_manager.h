/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F45K20
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
*/

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set BUTTON aliases
#define BUTTON_TRIS               TRISB0
#define BUTTON_LAT                LATB0
#define BUTTON_PORT               PORTBbits.RB0
#define BUTTON_WPU                WPUB0
#define BUTTON_ANS                ANS12
#define BUTTON_SetHigh()    do { LATB0 = 1; } while(0)
#define BUTTON_SetLow()   do { LATB0 = 0; } while(0)
#define BUTTON_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define BUTTON_GetValue()         PORTBbits.RB0
#define BUTTON_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define BUTTON_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define BUTTON_SetPullup()    do { WPUB0 = 1; } while(0)
#define BUTTON_ResetPullup()   do { WPUB0 = 0; } while(0)
#define BUTTON_SetAnalogMode()   do { ANS12 = 1; } while(0)
#define BUTTON_SetDigitalMode()   do { ANS12 = 0; } while(0)
// get/set SCL aliases
#define SCL_TRIS               TRISC3
#define SCL_LAT                LATC3
#define SCL_PORT               PORTCbits.RC3
#define SCL_SetHigh()    do { LATC3 = 1; } while(0)
#define SCL_SetLow()   do { LATC3 = 0; } while(0)
#define SCL_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define SCL_GetValue()         PORTCbits.RC3
#define SCL_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

// get/set SDA aliases
#define SDA_TRIS               TRISC4
#define SDA_LAT                LATC4
#define SDA_PORT               PORTCbits.RC4
#define SDA_SetHigh()    do { LATC4 = 1; } while(0)
#define SDA_SetLow()   do { LATC4 = 0; } while(0)
#define SDA_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define SDA_GetValue()         PORTCbits.RC4
#define SDA_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

// get/set LED0_EXCEPTION aliases
#define LED0_EXCEPTION_TRIS               TRISD0
#define LED0_EXCEPTION_LAT                LATD0
#define LED0_EXCEPTION_PORT               PORTDbits.RD0
#define LED0_EXCEPTION_SetHigh()    do { LATD0 = 1; } while(0)
#define LED0_EXCEPTION_SetLow()   do { LATD0 = 0; } while(0)
#define LED0_EXCEPTION_Toggle()   do { LATD0 = ~LATD0; } while(0)
#define LED0_EXCEPTION_GetValue()         PORTDbits.RD0
#define LED0_EXCEPTION_SetDigitalInput()    do { TRISD0 = 1; } while(0)
#define LED0_EXCEPTION_SetDigitalOutput()   do { TRISD0 = 0; } while(0)

// get/set LED1 aliases
#define LED1_TRIS               TRISD1
#define LED1_LAT                LATD1
#define LED1_PORT               PORTDbits.RD1
#define LED1_SetHigh()    do { LATD1 = 1; } while(0)
#define LED1_SetLow()   do { LATD1 = 0; } while(0)
#define LED1_Toggle()   do { LATD1 = ~LATD1; } while(0)
#define LED1_GetValue()         PORTDbits.RD1
#define LED1_SetDigitalInput()    do { TRISD1 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISD1 = 0; } while(0)

// get/set LED2 aliases
#define LED2_TRIS               TRISD2
#define LED2_LAT                LATD2
#define LED2_PORT               PORTDbits.RD2
#define LED2_SetHigh()    do { LATD2 = 1; } while(0)
#define LED2_SetLow()   do { LATD2 = 0; } while(0)
#define LED2_Toggle()   do { LATD2 = ~LATD2; } while(0)
#define LED2_GetValue()         PORTDbits.RD2
#define LED2_SetDigitalInput()    do { TRISD2 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISD2 = 0; } while(0)

// get/set LED3 aliases
#define LED3_TRIS               TRISD3
#define LED3_LAT                LATD3
#define LED3_PORT               PORTDbits.RD3
#define LED3_SetHigh()    do { LATD3 = 1; } while(0)
#define LED3_SetLow()   do { LATD3 = 0; } while(0)
#define LED3_Toggle()   do { LATD3 = ~LATD3; } while(0)
#define LED3_GetValue()         PORTDbits.RD3
#define LED3_SetDigitalInput()    do { TRISD3 = 1; } while(0)
#define LED3_SetDigitalOutput()   do { TRISD3 = 0; } while(0)

// get/set LED4 aliases
#define LED4_TRIS               TRISD4
#define LED4_LAT                LATD4
#define LED4_PORT               PORTDbits.RD4
#define LED4_SetHigh()    do { LATD4 = 1; } while(0)
#define LED4_SetLow()   do { LATD4 = 0; } while(0)
#define LED4_Toggle()   do { LATD4 = ~LATD4; } while(0)
#define LED4_GetValue()         PORTDbits.RD4
#define LED4_SetDigitalInput()    do { TRISD4 = 1; } while(0)
#define LED4_SetDigitalOutput()   do { TRISD4 = 0; } while(0)

// get/set LED6 aliases
#define LED6_TRIS               TRISD5
#define LED6_LAT                LATD5
#define LED6_PORT               PORTDbits.RD5
#define LED6_SetHigh()    do { LATD5 = 1; } while(0)
#define LED6_SetLow()   do { LATD5 = 0; } while(0)
#define LED6_Toggle()   do { LATD5 = ~LATD5; } while(0)
#define LED6_GetValue()         PORTDbits.RD5
#define LED6_SetDigitalInput()    do { TRISD5 = 1; } while(0)
#define LED6_SetDigitalOutput()   do { TRISD5 = 0; } while(0)

// get/set LED5 aliases
#define LED5_TRIS               TRISD6
#define LED5_LAT                LATD6
#define LED5_PORT               PORTDbits.RD6
#define LED5_SetHigh()    do { LATD6 = 1; } while(0)
#define LED5_SetLow()   do { LATD6 = 0; } while(0)
#define LED5_Toggle()   do { LATD6 = ~LATD6; } while(0)
#define LED5_GetValue()         PORTDbits.RD6
#define LED5_SetDigitalInput()    do { TRISD6 = 1; } while(0)
#define LED5_SetDigitalOutput()   do { TRISD6 = 0; } while(0)

// get/set LED7 aliases
#define LED7_TRIS               TRISD7
#define LED7_LAT                LATD7
#define LED7_PORT               PORTDbits.RD7
#define LED7_SetHigh()    do { LATD7 = 1; } while(0)
#define LED7_SetLow()   do { LATD7 = 0; } while(0)
#define LED7_Toggle()   do { LATD7 = ~LATD7; } while(0)
#define LED7_GetValue()         PORTDbits.RD7
#define LED7_SetDigitalInput()    do { TRISD7 = 1; } while(0)
#define LED7_SetDigitalOutput()   do { TRISD7 = 0; } while(0)


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
*/