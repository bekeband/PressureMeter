/* 
 * File:   BMP180.h
 * Author: user
 *
 * Created on 2015. november 28., 7:21
 */

#ifndef BMP180_H
#define	BMP180_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

//#define DEV_ADDRESS 0x77
#define DEV_ADDRESS           0x77
#define DEV_ID_BYTE           0x55
#define SOFT_RESET_REGISTER   0xE0
#define MEAS_CONTROL_REGISTER 0xF4
#define CALIB_DATAS_BEGIN_REG 0xAA
#define CALIB_DATAS_END_REG   0xBF

#define OUT_MSB_REG           0xF6
#define OUT_LSB_REG           0xF7
#define OUT_XSB_REG           0xF8

#define READ_UNCOMP_TEMP_DATA 0x2E
#define READ_UNCOMP_PRES_DATA 0x34

#define SOFT_RESET_COMMAND_CODE 0xB6

#define ADDR_ID_REG 0xD0

typedef union  {
  struct {
    int16_t ac1;  /**<calibration ac1 data*/
    int16_t ac2;/**<calibration ac2 data*/
    int16_t ac3;/**<calibration ac3 data*/
    uint16_t ac4;/**<calibration ac4 data*/
    uint16_t ac5;/**<calibration ac5 data*/
    uint16_t ac6;/**<calibration ac6 data*/
    int16_t b1;/**<calibration b1 data*/
    int16_t b2;/**<calibration b2 data*/
    int16_t mb;/**<calibration mb data*/
    int16_t mc;/**<calibration mc data*/
    int16_t md;/**<calibration md data*/
  };
  struct {
    int16_t WBUF[11];
  };
  struct {
    uint8_t BUF[22];
  };
}S_CALIB_DATA;

typedef S_CALIB_DATA* P_CALIB_DATA;

typedef union {
  struct {
    unsigned OSS: 2;
    unsigned SCO: 1;
    unsigned MCONT: 5;        
  };
  struct {
    uint8_t byteval;    
  };
}S_MEAS_CNTRL;
  
uint8_t GetIDByte();
int Test_BMP180_and_IDByte();
void StartMeasurement();
void ReadCalibrationDatas(P_CALIB_DATA CALIB_DATA);
int16_t ReadUncompTemperature();
int24_t ReadUncompPressure(uint8_t mode);
float CalculateTemperature(int16_t uncomp_temp);
float CalculatePressure(int16_t uncomp_pressure);
void SoftReset();
S_MEAS_CNTRL GetMeasurementControl();
void SetMeasurementControl(S_MEAS_CNTRL cntrl);

#ifdef	__cplusplus
}
#endif

#endif	/* BMP180_H */

