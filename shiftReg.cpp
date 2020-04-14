
#include "Arduino.h"
#include "shiftReg.h"


// Constructor
shiftReg::shiftReg (int data_pin, int clock_pin, int oe_pin, int register_size, bool MSB) {
  
  _data_pin = data_pin;
  _clock_pin = clock_pin;
  _oe_pin = oe_pin;
  _register_size = register_size;
  _MSB = MSB;
  
  pinMode (_data_pin, OUTPUT);
  pinMode (_clock_pin, OUTPUT);
  pinMode (_oe_pin, OUTPUT);
  
  digitalWrite (_oe_pin, LOW);
  digitalWrite (_data_pin, LOW);
  digitalWrite (_clock_pin, LOW);
  
}


void shiftReg::updateRegister () {
  
  if (MSB == 1) {
    
    #define __BITFIRST "MSBFIRST"
    
  }
  else {
    
    #define __BITFIRST "LSBFIRST"
    
  }
    
  shiftOut (_data_pin, _clock_pin, __BITFIRST, _shift_data);
  
}


void shiftReg::shiftData (byte shift_data) {
  
  _shift_data = shift_data;
  
  updateRegister ();
  
}


void shiftReg::allOne () {
    
  _shift_data = ON;
  
  updateRegister ();
  
}


void shiftReg::allZero () {
    
  _shift_data = OFF;
  
  updateRegister ();
  
  
}


byte shiftReg::readOut () {
  
  return (_shift_data);
  
}
