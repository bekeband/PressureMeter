
#include <stdio.h>
#include "delay.h"
#include "exceptions.h"

void ExecuteExceptions(bool is_display, int code, const char* PrgInfo, const char* text)
{ const char DSP_BUFFER[LCD_COLS + 1]; int i, j;
  /* If exist display, and can we printing exceptions information. */
  if (is_display)
  {
    LCD_I2C_Clear();
    LCD_I2C_Home();
    sprintf(DSP_BUFFER, "EXC");
    LCD_I2C_PrintStr(DSP_BUFFER);
  } else
    /* If have'nt display, and we can blinking LED, or beep only.  */
  {
    
  }
  /* Infinity loop */
  while (1)
  {
    LCD_I2C_NoBacklight();
    for (i = 0; i < code; i++)
    {
      LED0_EXCEPTION_SetHigh();
      delayms(50);
      LED0_EXCEPTION_SetLow();
      delayms(150);
    }
    delayms((5 - code) * 200);
//    LED0_EXCEPTION_Toggle();
    LCD_I2C_Backlight();
    delayms(1000);
  }
}
