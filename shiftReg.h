

#ifndef shiftReg_h
#define shiftReg_h

#include "Arduino.h"


#define OUT_TYPE Serial   // Output type
#define MAX_SIZE 128    // Maximum shift register size

class shiftReg {
  
  public:
    shiftReg (int data_pin, int clock_pin, int oe_pin, int register_size, bool MSB = true);
    void shift (int shift_data);
  
  private:
    bool _data_bit[MAX_SIZE];   // Storage for binary data
    bool _data_buffer[MAX_SIZE];   // Buffer if MSB is enabled
  
    int _data_pin;    
    int _clock_pin;
    int _oe_pin;
    int _register_size;
    bool _MSB;
  
    int _shift_data;
  
}

#endif
