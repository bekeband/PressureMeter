

#include "i2cmaster.h"


uint8_t Write_I2C_Master(uint8_t* writeBuffer, uint8_t length, uint16_t slaveDeviceAddress)
{ int timeOut = 0;
  I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
  while(status != I2C_MESSAGE_FAIL)
  {
    // write one byte to EEPROM (3 is the number of bytes to write)
    I2C_MasterWrite(  writeBuffer, length, slaveDeviceAddress, &status);
    // wait for the message to be sent or status has changed.
    while(status == I2C_MESSAGE_PENDING);
    if (status == I2C_MESSAGE_COMPLETE) break;
    /* if status is  I2C_MESSAGE_ADDRESS_NO_ACK, or I2C_DATA_NO_ACK,
    * The device may be busy and needs more time for the last
    * write so we can retry writing the data, this is why we
    * use a while loop here
    * check for max retry and skip this byte
    * */
    if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX) break;
    else timeOut++;
    if (status == I2C_MESSAGE_FAIL) { break;};
  };
  return status;
};
