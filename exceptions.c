
#include "delay.h"
#include "exceptions.h"

void ExecuteExceptions(bool is_display, const char* PrgInfo, const char* text)
{ const char DSP_BUFFER[LCD_COLS + 1];
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
    delayms(500);
    LED0_EXCEPTION_Toggle();
  }
}
