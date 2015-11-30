
#include <xc.h>
#include "delay.h"

void delay(int count, int factor)
{ int i;
  TMR1_StopTimer();
  TMR1_WriteTimer(factor);
  for (i = 0; i < count; i++)
  {
    TMR1_StartTimer();
    while (!TMR1_HasOverflowOccured());
    PIR1bits.TMR1IF = 0;
    TMR1_StopTimer();
    TMR1_WriteTimer(factor);
  }
}

void delayms(int count)
{
  delay(count, MSEC_FACTOR);
}

void delayus(int count)
{
  delay(count, USEC_FACTOR);
}