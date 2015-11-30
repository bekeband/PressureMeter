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
#define DEV_ADDRESS 0x76
#define DEV_ID_BYTE 0x55

#define ADDR_ID_REG 0xD0

uint8_t GetIDByte();
void StartMeasurement();
void ReadCalibrationDatas();
int16_t ReadUncompTemperature();
int16_t ReadUncompPressure();
float CalculateTemperature(int16_t uncomp_temp);
float CalculatePressure(int16_t uncomp_pressure);

struct s_calib_data_struct {
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

#ifdef	__cplusplus
}
#endif

#endif	/* BMP180_H */

