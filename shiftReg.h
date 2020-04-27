

#ifndef shiftReg_h
#define shiftReg_h

#include "Arduino.h"


#define VAR_SIZE    0x08
//#define OUT_TYPE    Serial   // Output type

#ifndef ON
  #define ON      0xFF
#endif

#ifndef OFF
  #define OFF     0x00
#endif

#define SHIFT_REGISTER_INDICATOR    // For usage of 1602A


class shiftReg {
  
  public:
    shiftReg (uint16_t data_pin, uint16_t clock_pin, uint16_t latch_pin, bool MSB);
    void shiftData (byte shift_data);
    void updateRegister ();
    void allOne ();
    void allZero ();
  
    byte readOut ();    // Reading out shift_data
  
  private:
    uint16_t _data_pin;    // Private variables for pins
    uint16_t _clock_pin;
    uint16_t _latch_pin;
    bool _MSB;
  
    byte _shift_data;
  
};

#endif
