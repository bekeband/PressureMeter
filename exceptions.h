/* 
 * File:   exceptions.h
 * Author: user
 *
 * Created on 2015. november 30., 11:58
 */

#ifndef EXCEPTIONS_H
#define	EXCEPTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "LiquidCrystal_I2C.h"
#include "mcc_generated_files/mcc.h"

#define EXC_NO_ADDR27H  0
#define EXC_NO_ADDR77H  1
#define EXC_NO_BMP_180  2
#define EXC_NO_DISP     3

void ExecuteExceptions(bool is_display, int code, const char* P, const char* I);

#ifdef	__cplusplus
}
#endif

#endif	/* EXCEPTIONS_H */

