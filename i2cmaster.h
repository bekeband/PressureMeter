/* 
 * File:   i2cmaster.h
 * Author: user
 *
 * Created on 2015. november 30., 10:48
 */

#ifndef I2CMASTER_H
#define	I2CMASTER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "mcc_generated_files/mcc.h"

#define SLAVE_I2C_GENERIC_RETRY_MAX     10

uint8_t Write_I2C_Master(uint8_t* writeBuffer, uint8_t length, uint16_t slaveDeviceAddress);
uint8_t Read_I2C_Master(uint8_t* readBuffer, uint8_t length, uint16_t slaveDeviceAddress);

#ifdef	__cplusplus
}
#endif

#endif	/* I2CMASTER_H */

