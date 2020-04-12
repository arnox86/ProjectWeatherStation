

#ifndef shiftReg_h
#define shiftReg_h

#include "Arduino.h"


class shiftReg {
  
  public:
    shiftReg (int data_pin, int clock_pin, int oe_pin, int register_size, bool MSB = true);
    void shift (int shift_data);
  
  private:
    boolean _data_bit[128];
    int _data_pin;
    int _clock_pin;
    int _oe_pin;
    int _register_size;
    bool _MSB;
  
}

#endif
