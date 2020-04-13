
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
    
    #define BITFIRST "MSBFIRST"
    
  }
  else {
    
    #define BITFIRST "LSBFIRST"
    
  }
  
  for (int _upt_cnt = 0; _upt_cnt < _register_size; _upt_cnt++) {
    
    shiftOut (_data_pin, _clock_pin, BITFIRST, _shift_data[_upt_cnt]);
    
  }
  
}


void shiftReg::shiftData (byte shift_data[MAX_SIZE]) {
  
  if (_MSB = 1) {
  
      for (int _inh_cnt = 0; _inh_cnt < _register_size; _inh_cnt++) {
      
        _shift_data[_inh_cnt] = shift_data[_inh_cnt];
      
      }
          
  }
  else {
    
      for (int _inh_cnt = 0; _inh_cnt < _register_size; _inh_cnt++) {
      
        _shift_data[_inh_cnt] = shift_data[_register_size - _inh_cnt];
      
      }
    
  }
  
  updateRegister ();
  
}


void shiftReg::allOne () {
  
  for (int _on_cnt = 0; _on_cnt < _register_size; _on_cnt++) {
    
    _shift_data[_on_cnt] = ON;
    
  }
  
  updateRegister ();
  
}


void shiftReg::allZero () {
  
  for (int _off_cnt = 0; _off_cnt < _register_size; _off_cnt++) {
    
    _shift_data[_off_cnt] = OFF;
    
  }
  
  updateRegister ();
  
  
}


byte shiftReg::readOut (int byte_number) {
  
  return (_shift_data[byte_number]);
  
}
