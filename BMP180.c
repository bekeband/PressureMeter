
#include <stdint.h>
#include <stdio.h>
#include "BMP180.h"
#include "i2cmaster.h"
#include "exceptions.h"
#include "delay.h"
#include "mcc_generated_files/mcc.h"

S_CALIB_DATA CALIB_DATA;

int Test_BMP180_and_IDByte()
{
  return (GetIDByte() == DEV_ID_BYTE);
}

void SetMeasurementControl(S_MEAS_CNTRL cntrl)
{ uint8_t BUF[2] = {MEAS_CONTROL_REGISTER};
  BUF[1] = cntrl.byteval;
  I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;;
  I2C_MasterWrite(&BUF, 2, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
}

S_MEAS_CNTRL GetMeasurementControl()
{ uint8_t REG_ADDR = MEAS_CONTROL_REGISTER;
  S_MEAS_CNTRL retval;
  I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;;
  I2C_MasterWrite(&REG_ADDR, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  I2C_MasterRead(&REG_ADDR, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  retval.byteval = REG_ADDR;
  return retval;
}

/* Software reset */

void SoftReset()
{ uint8_t BUF[2] = {SOFT_RESET_REGISTER, SOFT_RESET_COMMAND_CODE};
  I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;;
  I2C_MasterWrite(&BUF, 2, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
}

/* Read with exceptions to safety read. */

uint8_t GetIDByte()
{ uint8_t ID_REG = ADDR_ID_REG; I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
  status = Write_I2C_Master(&ID_REG, 1, DEV_ADDRESS);
  if (status == I2C_MESSAGE_COMPLETE)
  {
    status = Read_I2C_Master(&ID_REG, 1, DEV_ADDRESS);
    if (status == I2C_MESSAGE_COMPLETE)
    {
      return ID_REG;
    } else
    {
      /* No pressure sensor seriously error -> exception code.*/
      ExecuteExceptions(1, EXC_NO_ADDR77H, "", "");
    }
  } else
  {
    /* No pressure sensor seriously error -> exception code.*/
    ExecuteExceptions(1, 3, "", "");
  }
  return status;
}

void StandardCalibDatas(int i)
{
  CALIB_DATA.ac1 = 408;
  CALIB_DATA.ac2 = -72;
  CALIB_DATA.ac3 = -14383;
  CALIB_DATA.ac4 = 32741;
  CALIB_DATA.ac5 = 32757;
  CALIB_DATA.ac6 = 23153;
  CALIB_DATA.b1 = 6190;
  CALIB_DATA.b2 = 4;
  CALIB_DATA.mb = -32768;
  CALIB_DATA.mc = -8711;
  CALIB_DATA.md = 2868;
};
		// Example from http://wmrx00.sourceforge.net/Arduino/BMP180-Calcs.pdf
		// AC1 = 7911; AC2 = -934; AC3 = -14306; AC4 = 31567; AC5 = 25671; AC6 = 18974;
		// VB1 = 5498; VB2 = 46; MB = -32768; MC = -11075; MD = 2432;

void ReadCalibrationDatas()
{ uint8_t i; I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
  uint8_t ID_REG = CALIB_DATAS_BEGIN_REG;
  uint8_t DATAH, DATAL;
  for (i = 0; i < 11; /*(sizeof(CALIB_DATA))*/ i++)
  {
    I2C_MasterWrite(&ID_REG, 1, DEV_ADDRESS, &status);
    while (status == I2C_MESSAGE_PENDING);
    I2C_MasterRead(&DATAH, 1, DEV_ADDRESS, &status);
    while (status == I2C_MESSAGE_PENDING);
    ID_REG++;
    I2C_MasterWrite(&ID_REG, 1, DEV_ADDRESS, &status);
    while (status == I2C_MESSAGE_PENDING);
    I2C_MasterRead(&DATAL, 1, DEV_ADDRESS, &status);
    while (status == I2C_MESSAGE_PENDING);
    ID_REG++;
    CALIB_DATA.WBUF[i] = (DATAH * 256) + DATAL;
  }
}

int32_t ReadUncompTemperature()
{ uint8_t i; I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
  uint8_t BUF[2] = {MEAS_CONTROL_REGISTER, READ_UNCOMP_TEMP_DATA};
  uint8_t READ_REG = OUT_LSB_REG;
  uint8_t DATAL, DATAH;
  I2C_MasterWrite(&BUF, 2, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  delayms(5);
  I2C_MasterWrite(&READ_REG, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  I2C_MasterRead(&DATAL, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  READ_REG = OUT_MSB_REG;
  I2C_MasterWrite(&READ_REG, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  I2C_MasterRead(&DATAH, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  return (DATAL + (DATAH * 256));
}

int32_t ReadUncompPressure(uint8_t mode)
{ uint8_t i; I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
  uint8_t BUF[2] = {MEAS_CONTROL_REGISTER};
  uint8_t READ_REG = OUT_LSB_REG;
  int32_t retval;
  int wait_time;
//  S_PRESSURE_DATA indata;
  uint8_t INDATA;

  switch (mode)
  {
    case  0: wait_time =  5; break;
    case  1: wait_time =  8; break;
    case  2: wait_time = 14; break;
    case  3: wait_time = 26; break;
  }

  BUF[1] = READ_UNCOMP_PRES_DATA | (mode << 8);

  I2C_MasterWrite(&BUF, 2, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  delayms(wait_time);
  /* First out lsb register check. */
  I2C_MasterWrite(&READ_REG, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  I2C_MasterRead(&INDATA, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  retval = INDATA << 8;
  /* Then out MSB register ask. */
  READ_REG = OUT_MSB_REG;
  I2C_MasterWrite(&READ_REG, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  I2C_MasterRead(&INDATA, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  retval += (INDATA * 0x010000L);
  READ_REG = OUT_XSB_REG;
  /* At the end we curiously the XLSB register. */
  I2C_MasterWrite(&READ_REG, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  I2C_MasterRead(&INDATA, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  retval += INDATA;
  retval >>= (8 - mode);
  return retval;
}

int32_t ComputeB5(int32_t UT) {
  int32_t X1 = (UT - (int32_t)CALIB_DATA.ac6) * ((int32_t)CALIB_DATA.ac5) >> 15;
  int32_t X2 = ((int32_t)CALIB_DATA.mc << 11) / (X1+(int32_t)CALIB_DATA.md);
  return X1 + X2;
}

float GetTemperature(int32_t B5)
{ int32_t temp;
  temp = (B5+8) >> 4;
  temp /= 10; 
  return temp;  
}

int32_t CalculatePressure(int32_t UP, int32_t B5, uint8_t mode)
{ int32_t  B6, X1, X2, X3, B3, B4, B7, p;

  B6 = B5 - 4000;

  X1 = ((int32_t)CALIB_DATA.b2 * ( (B6 * B6)>>12 )) >> 11;

  X2 = ((int32_t)CALIB_DATA.ac2 * B6) >> 11;

  X3 = X1 + X2;
  B3 = ((((int32_t)CALIB_DATA.ac1*4 + X3) << mode) + 2) / 4;

  X1 = ((int32_t)CALIB_DATA.ac3 * B6) >> 13;
  X2 = ((int32_t)CALIB_DATA.b1 * ((B6 * B6) >> 12)) >> 16;
  X3 = ((X1 + X2) + 2) >> 2;

  B4 = ((uint32_t)CALIB_DATA.ac4 * (uint32_t)(X3 + 32768)) >> 15;

  B7 = ((uint32_t)UP - B3) * (uint32_t)(50000UL >> mode);

  if ((uint32_t)B7 < 0x80000000L) {
    p = (uint32_t)(B7 * 2) / B4;
  } else {
    p = (uint32_t)(B7 / B4) * 2;
  }

  X1 = (p >> 8L) * (p >> 8L);

  X1 = (X1 * 3038L) >> 16L;

  X2 = (-7357L * p) / 65536L;

  p = p + ((X1 + X2 + (int32_t)3791L)>>4);
  return p;
}
