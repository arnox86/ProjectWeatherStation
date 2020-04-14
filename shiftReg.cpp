
#include "Arduino.h"
#include "shiftReg.h"


// Constructor
shiftReg::shiftReg (uint16_t data_pin, uint16_t clock_pin, uint16_t latch_pin, bool MSB) {
  
  _data_pin = data_pin;
  _clock_pin = clock_pin;
  _latch_pin = latch_pin;
  _MSB = MSB;
  
  pinMode (_data_pin, OUTPUT);
  pinMode (_clock_pin, OUTPUT);
  pinMode (_latch_pin, OUTPUT);
  
  digitalWrite (_latch_pin, LOW);
  digitalWrite (_data_pin, LOW);
  digitalWrite (_clock_pin, LOW);
  
}


void shiftReg::updateRegister () {
  
  if (_MSB == 1) {
    
    #define _BITFIRST 'MSBFIRST'
    
  }
  else {
    
    #define _BITFIRST 'LSBFIRST'
    
  }
    
  digitalWrite (_latch_pin, LOW);

  shiftOut (_data_pin, _clock_pin, _BITFIRST, _shift_data);
  
  digitalWrite (_latch_pin, HIGH);

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
