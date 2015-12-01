
#include <stdint.h>
#include "BMP180.h"
#include "i2cmaster.h"
#include "exceptions.h"
#include "delay.h"
#include "mcc_generated_files/mcc.h"

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

void ReadCalibrationDatas(P_CALIB_DATA CALIB_DATA)
{ uint8_t i; I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
  uint8_t ID_REG = CALIB_DATAS_BEGIN_REG;
  uint8_t DATA;
  for (i = 0; i < 22; /*(sizeof(CALIB_DATA))*/ i++)
  {
    I2C_MasterWrite(&ID_REG, 1, DEV_ADDRESS, &status);
    while (status == I2C_MESSAGE_PENDING);
    I2C_MasterRead(&DATA, 1, DEV_ADDRESS, &status);
    while (status == I2C_MESSAGE_PENDING);
    CALIB_DATA->BUF[i] = DATA;
    ID_REG++;
  }
}

int16_t ReadUncompTemperature()
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
  return (DATAL + (DATAH << 8));
}

int24_t ReadUncompPressure(uint8_t mode)
{ uint8_t i; I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
  uint8_t BUF[2] = {MEAS_CONTROL_REGISTER};
  uint8_t READ_REG = OUT_LSB_REG;
  int wait_time;
  uint8_t DATAL, DATAM, DATAH;

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

  I2C_MasterWrite(&READ_REG, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  I2C_MasterRead(&DATAL, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);

  READ_REG = OUT_MSB_REG;
  I2C_MasterWrite(&READ_REG, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  I2C_MasterRead(&DATAM, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);

  READ_REG = OUT_XSB_REG;

  I2C_MasterWrite(&READ_REG, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);
  I2C_MasterRead(&DATAH, 1, DEV_ADDRESS, &status);
  while (status == I2C_MESSAGE_PENDING);

  return (DATAL + (DATAM << 8) + (DATAH << 16));
}