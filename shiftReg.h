

#ifndef shiftReg_h
#define shiftReg_h

#include "Arduino.h"


#define OUT_TYPE Serial   // Output type

class shiftReg {
  
  public:
    shiftReg (int data_pin, int clock_pin, int oe_pin, int register_size, bool MSB = true);
    void shift (int shift_data);
  
  private:
    bool _data_bit[128];   // Storage for binary data
    bool _dtaa_buffer[128];   // Buffer if MSB is enabled
  
    int _data_pin;    
    int _clock_pin;
    int _oe_pin;
    int _register_size;
    bool _MSB;
  
    int _shift_data;
  
}

#endif
