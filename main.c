/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F45K20
        Driver Version    :  2.00
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
#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"
#include "delay.h"
#include "LiquidCrystal_I2C.h"
#include "exceptions.h"
#include "BMP180.h"

uint8_t count = 0;
uint8_t DISP_BUFFER[LCD_COLS + 1];

void PrintBinary(uint8_t value)
{ int j; uint8_t i = 0x80;
  for (j = 0; j < 8; j++)
  {
    if (value & i) DISP_BUFFER[j] = '1';
    else DISP_BUFFER[j] = '0';
    i >>= 1;
  }
  DISP_BUFFER[j] = '\0';
}

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    /* Start program, and I/O testing. */

    Init_LCD();

    if (!Test_BMP180_and_IDByte())
    {
      ExecuteExceptions(true, EXC_NO_BMP_180, "", "");
    }

    LCD_I2C_Backlight();
    LCD_I2C_Display();
    LCD_I2C_Clear();

    S_MEAS_CNTRL meas_control;
    meas_control.SCO = 0b1;
    meas_control.OSS = 0b11;
//    SetMeasurementControl(meas_control);

    ReadCalibrationDatas();
    uint24_t upress;
    float fpress;
    float utemp;
    float ctemp;
    float ftemp;

    int u = 0;

    while (1)
    {
      utemp = ReadUncompTemperature();
      ctemp = CalculateTemperature(utemp);
      ftemp = ctemp / 10f;
      /* Out the temperature value. */
      sprintf(DISP_BUFFER, "TEMP = %7.1f", ftemp);
      LCD_I2C_SetCursor(0, 0);
      LCD_I2C_PrintStr(DISP_BUFFER);

      upress = ReadUncompPressure(0b00);
//      sprintf(DISP_BUFFER, "%3i, %3i, %3i", upress.LSB, upress.MSB, upress.XLSB);
      fpress = upress;
      sprintf(DISP_BUFFER, "%8.1f", fpress);
      LCD_I2C_SetCursor(0, 1);
      LCD_I2C_PrintStr(DISP_BUFFER);
//      sprintf(DISP_BUFFER, "%8u %8u", CALIB_DATA.ac5, CALIB_DATA.ac6);
//      while (BUTTON_GetValue());
      delayms(500);
      u++;
      if (u == 11) u = 0;
    }

    while (1)
    {
      meas_control = GetMeasurementControl();
      PrintBinary(meas_control.byteval);
      LCD_I2C_SetCursor(0, 1);
      LCD_I2C_PrintStr(DISP_BUFFER);
      while (1);
    }

    sprintf(DISP_BUFFER, "PR ID:%xH", GetIDByte());
    LCD_I2C_SetCursor(0, 1);
    LCD_I2C_PrintStr(DISP_BUFFER);
    
    while (1)
    {
      delayms(50);
      PORTD = count++;
      LCD_I2C_SetCursor(0, 0);
      sprintf(DISP_BUFFER, "CNT = %5i", count);
      LCD_I2C_PrintStr(DISP_BUFFER);
    }
}
/**
 End of File
*/