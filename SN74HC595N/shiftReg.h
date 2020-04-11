

#ifndef shiftReg_h
#define shiftReg_h

#include "Arduino.h"


/* Uncomment for some nice debug helps */
//#define DEBUG_MESSAGE

#define DEBUG_BEGIN Serial    // Output type of debug messages

#ifndef DEBUG_MESSAGE
  #define DEBUG_PRINT (...) { DEBUG_BEGIN.print (__VA_ARG__); }
  #define DEBUG_PRINTLN (...) { DEBUG_BEGIN.println (__VA_ARG__); }

#else
  #define DEBUG_PRINT (...) {}    // Placeholder if disabled
  #define DEBUG_PRINTLN (...) {}

#endif


class shiftReg {
  
  public:
    shiftReg (int data_pin, int clock_pin, int oe_pin, int register_size, boolean MSB = true);
    void shift (int shift_data);
  
  private:
    
  
}

#endif
