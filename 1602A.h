/*
*
*/


#ifndef 1602A_h
#define 1602A_h

#include "Arduino.h"
#include "shiftReg.h"


#ifndef SH_REG

  #ifndef SHIFT_REGISTER_INDICATOR
    #define SH_REG 0

  #else
    #define SH_REG 1

  #endif
#endif


#ifndef OUT_TYPE
  #define OUT_TYPE Serial    // Output type
#endif


#ifndef ON
  #define ON 0xFF
#endif

#ifndef OFF
  #define OFF 0b00000000    // To be sure ;)
#endif


class 1602A {
  
  public:
    uint16_t pin_input[8];
  
    1602A (pin_input[0], pin_input[1], pin_input[2], pin_input[3], pin_input[4], pin_input[5], pin_input[6], pin_input[7], 
           uint16_t enable_pin, uint16_t rs_pin, uint16_t bright_pin, uint16_t brightness, 
           uint8_t operation_mode);
  
    void initShiftRegister (uint16_t data_pin, uint16_t clock_pin, uint16_t latch_pin);
    
  
  private:
    uint16_t _dataPin[8];
    uint16_t _pbuffer[10];
    
    uint8_t _sr_assignment[8];    // Assignment of output and output pins
    uint8_t _sr_output;   // Output byte for shift register
  
    bool _sr_init;    // Indicates if shift register is used, 0 by default
    bool _8bit_mode;
    
}


#endif
