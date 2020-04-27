/*
*
*/


#include "Arduino.h"
#include "1602A.h"

#include "shiftReg.h"


1602A::1602A (pin_input[0], pin_input[1], pin_input[2], pin_input[3], pin_input[4], pin_input[5], pin_input[6], pin_input[7], 
              uint16_t enable_pin, uint16_t rs_pin, uint16_t bright_pin, uint16_t brightness, 
              uint8_t operation_mode) {
  
  _sr_init = 0;   // 0 by default
  
  for (uint8_t _piv = 0; _piv < 8; _piv++) {
    
    _dataPin[_piv] = pin_input[_piv];
    
  }
  
  pinMode (bright_pin, OUTPUT);
  
  for (uint8_t brtcnt = 0; brtcnt < brightness; brtcnt++) {
    
    analogWrite (bright_pin, brtcnt);   // Slowly increasing brightness
    delay (1);
    
  }
  
  analogWrite (bright_pin, brightness);
  
  if (operation_mode == 8) _8bit_mode = 1;
  else if (operation_mode == 4) _8bit_mode = 0;   // Operation mode indication
  else {
    
    OUT_TYPE.print ("operation mode failure: bus mode not available; input: ");   // Debug message
    OUT_TYPE.println (operation_mode);
    return;
    
  }
  
}


void 1602A::initShiftRegister (uint16_t data_pin, uint16_t clock_pin, uint16_t latch_pin) {
  
  shiftReg sr_lcd (data_pin, clock_pin, latch_pin, 1);    // 1 for MSB first
  
  sr_lcd.setZero();
  
  _sr_init = 1;   // Shift register is used
  
  
  if (_8bit_mode == 0) {
    
    
    
  }
  
}
