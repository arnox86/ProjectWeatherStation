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


class 1602A {
  
  public:
  1602A (     );
    
  
  private:
    
    
  
}


#endif
