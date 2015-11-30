/* 
 * File:   delay.h
 * Author: user
 *
 * Created on 2015. november 23., 11:51
 */

#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/tmr1.h"

#define USEC_FACTOR 0xFFF0
#define MSEC_FACTOR 0xC180
  
void delayms(int count);
void delayus(int count);

#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

