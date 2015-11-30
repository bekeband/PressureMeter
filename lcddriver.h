/* 
 * File:   lcddriver.h
 * Author: user
 *
 * Created on 2015. október 9., 13:37
 */

#ifndef LCDDRIVER_H
#define	LCDDRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

#define DISPLAY_WIDTH   16

//#define		E       LATAbits.LA5 // RA5
//#define		RW			LATAbits.LA3 //RA3
//#define		RS			LATAbits.LA2 // RA2

#define		CLR_DISP		0x01
#define		DISP_ON			0x0C
#define		DISP_OFF		0x08
#define		CUR_HOME        0x02
#define		CUR_OFF 		0x0C
#define 	CUR_ON_UNDER    0x0E
#define		CUR_ON_BLINK    0x0F
#define 	CUR_LEFT        0x10
#define		CUR_RIGHT       0x14
#define		CUR_UP  		0x80
#define		CUR_DOWN		0xC0
#define		ENTER           0xC0
#define		DD_RAM_ADDR		0x80
#define		DD_RAM_ADDR2	0xC0

void InitLCD(void);
void LCD_Initialize(void);
void LCDOutChar(unsigned char data);
void LCDOutCmd(unsigned char data);
void LCDSendStr(unsigned char* str);
void LCDSendBuf(uint8_t* buf, int size);
void LCD_I2C_PORT_SetHigh(uint8_t mask);
void LCD_I2C_PORT_SetLow(uint8_t mask);
void LCD_I2C_WriteData(uint8_t data);
void LCD_Backlight_On();
void LCD_Backlight_Off();

#define DelayMs delay_msec
#define LCD_WIDTH 16
#define LCD_ROWS  2

/* define for I2C PCF 8574 LCD I2C I/O controller IC for LCD bits. */

#define PCF8574_ADDR  0x27

#define RS_BIT  0b00000001
#define RW_BIT  0b00000010
#define E_BIT   0b00000100
#define BL_BIT  0b00001000

#define D4_BIT  0b00010000
#define D5_BIT  0b00100000
#define D6_BIT  0b01000000
#define D7_BIT  0b10000000


#ifdef	__cplusplus
}
#endif

#endif	/* LCDDRIVER_H */

