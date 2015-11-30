
#include <xc.h>
#include <stdint.h>
#include "lcddriver.h"
#include "delay.h"
#include "mcc_generated_files/mcc.h"

volatile uint8_t BACKLIGHT_MASK;

void LCD_I2C_WriteData(uint8_t data)
{ I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
  I2C_MasterWrite(&data, 1, PCF8574_ADDR, &status);
  while(status == I2C_MESSAGE_PENDING);
}

uint8_t LCD_I2C_ReadData()
{ I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING; uint8_t data;
  I2C_MasterRead((uint8_t*)&data, 1, PCF8574_ADDR, &status);
  while(status == I2C_MESSAGE_PENDING);
  return data;
}

void LCD_Backlight_On()
{
  BACKLIGHT_MASK = BL_BIT;
  LCD_I2C_WriteData(BL_BIT);
}

void LCD_Backlight_Off()
{
  BACKLIGHT_MASK = 0x00;
  LCD_I2C_WriteData(0x00);
}

void LCD_I2C_PORT_SetHigh(uint8_t mask)
{ uint8_t data;
  data = LCD_I2C_ReadData();
  data |= mask;
  LCD_I2C_WriteData(data);
}

void LCD_I2C_PORT_SetLow(uint8_t mask)
{ uint8_t data;
  data = LCD_I2C_ReadData();
  data &= ~mask;
  PORTD = data;
  while (1);
  LCD_I2C_WriteData(data);
}

void E_Pulse(void) {
	LCD_I2C_PORT_SetHigh(E_BIT);
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
	LCD_I2C_PORT_SetLow(E_BIT);
}

void LCD_Initialize(void)
{
  LCD_I2C_WriteData(0x00);
	delayms(110);
  LCD_I2C_WriteData(0b00110000);
	E_Pulse();
	delayms(10);
  LCD_I2C_WriteData(0b00110000);
	E_Pulse();
	delayms(10);
  LCD_I2C_WriteData(0b00100000);
	E_Pulse();
	delayms(10);
  LCD_I2C_WriteData(0b10110000);
	E_Pulse();
/*	PORTC = 0b00000011;
	E_Pulse();
	delayms(10);
	PORTC = 0b00000011;
	E_Pulse();
	delayms(10);
	PORTC = 0b00000011;
	E_Pulse();
	delayms(10);
	PORTC = 0b00000010;
	E_Pulse();*/
}

// Init LCD  after reset
void InitLCD(void) {

	INTCON 	= 0x0;			// Disable inerupt
  ANSEL = 0x0;
	LCD_I2C_PORT_SetLow(RS_BIT);
	LCD_I2C_PORT_SetLow(RW_BIT);
	delayms(110);
	PORTC=0b00000011;
	E_Pulse();
	delayms(10);
	PORTC=0b00000011;
	E_Pulse();
	delayms(10);
	PORTC=0b00000011;
	E_Pulse();
	delayms(10);
	PORTC=0b00000010;
	E_Pulse();
}

void LCDOutChar(unsigned char data)
{
  delayms(1);
  LCD_I2C_WriteData((data & 0xF0) | BACKLIGHT_MASK);

//  LATC = ((data & 0xF0) >> 4);
  LCD_I2C_PORT_SetLow(RW_BIT);
  LCD_I2C_PORT_SetHigh(RS_BIT);
  E_Pulse();
  LCD_I2C_WriteData(((data & 0x0F) << 4) | BACKLIGHT_MASK);
//  LATC = (data & 0x0F);
  LCD_I2C_PORT_SetLow(RW_BIT);
  LCD_I2C_PORT_SetHigh(RS_BIT);
  E_Pulse();
}

void LCDOutCmd(unsigned char data)
{
  delayms(1);
  LCD_I2C_WriteData(data & 0xF0);
//  LATC = ((data & 0xF0) >> 4);
  LCD_I2C_PORT_SetLow(RW_BIT);
  LCD_I2C_PORT_SetLow(RS_BIT);
  E_Pulse();
  LCD_I2C_WriteData((data & 0x0F) << 4);
//  LATC = (data & 0x0F);
  LCD_I2C_PORT_SetLow(RW_BIT);
  LCD_I2C_PORT_SetLow(RS_BIT);
  E_Pulse();
}


void LCDSendStr(unsigned char* str)
{ int i;
	i=0;
	while(str[i]) {
		LCDOutChar(str[i]);
		i++;
	}
}

void LCDSendBuf(uint8_t* buf, int size)
{ int i;
  for (i = 0; i < size; i++)
    {
      LCDOutChar(buf[i]);
    }
}

