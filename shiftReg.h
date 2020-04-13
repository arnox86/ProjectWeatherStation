

#ifndef shiftReg_h
#define shiftReg_h

#include "Arduino.h"


#define VAR_SIZE    0x08
#define OUT_TYPE    Serial   // Output type
#define MAX_SIZE    0x10    // Maximum register size in bytes

#define ON      0xFF
#define OFF     0x00

#define SHIFT_REGISTER_INDICATOR    // For usage of 1602A


class shiftReg {
  
  public:
    shiftReg (int data_pin, int clock_pin, int oe_pin, int register_size, bool MSB);
    void shiftData (byte shift_data[MAX_SIZE]);
    void updateRegister ();
    void allOne ();
    void allZero ();
  
    byte readOut (int byte_number);
  
  private:
    int _data_pin;    // Private variables for pins
    int _clock_pin;
    int _oe_pin;
    int _register_size;
    bool _MSB;
  
    byte _shift_data[MAX_SIZE];
  
};

#endif
