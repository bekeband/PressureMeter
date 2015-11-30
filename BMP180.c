
#include <stdint.h>
#include "BMP180.h"
#include "i2cmaster.h"
#include "exceptions.h"
#include "mcc_generated_files/mcc.h"

uint8_t GetIDByte()
{ uint8_t ID_REG = ADDR_ID_REG; I2C_MESSAGE_STATUS status;
  status = Write_I2C_Master(&ID_REG, 1, DEV_ADDRESS);
  if (status == I2C_MESSAGE_COMPLETE)
  {

  } else
  {
    /* No pressure sensor seriously error -> exception code.*/
    ExecuteExceptions(true, "", "");
  }
  while(status == I2C_MESSAGE_PENDING);
  I2C_MasterRead(&ID_REG, 1, DEV_ADDRESS, &status);
  while(status == I2C_MESSAGE_PENDING);
  return ID_REG;
}
