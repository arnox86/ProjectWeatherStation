
/*
MIT License

Copyright (c) 2020 Benedikt Bursian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


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
  
    byte readOut ();    // Read out shift_data
  
  private:
    uint16_t _data_pin;    // Private variables for pins
    uint16_t _clock_pin;
    uint16_t _latch_pin;
    bool _MSB;
  
    byte _shift_data;
  
};

#endif
