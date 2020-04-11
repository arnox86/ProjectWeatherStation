

#ifndef shiftReg_h
#define shiftReg_h

#include "Arduino.h"


class shiftReg {
  
  public:
    shiftReg (int data_pin, int clock_pin, int oe_pin, int register_size, boolean bit_first);
    void shift (int shift_data);
  
  private:
    
  
}

#endif
