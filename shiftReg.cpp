
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
  
}


void shiftReg::shift (int shift_data) {
  
  _shift_data = shift_data;
  
  // Converting _shift_data to binary
  for (int _bit_count = 0; _bit_count < _register_size; _bit_count++) {
    
    if (((_shift_data >> (_register_size - (_bit_count + 1))) & 1) != 0) {
      
      _data_bit[_bit_count] = 1;
      
    }
    else {
      
      _data_bit[_bit_count] = 0;
      
    }
    
  }
  
  // Inverting into MSB order if enabled
  if (_MSB) {
    
    for (int _inv_cnt = 0; _inv_cnt < _register_size; _inv_cnt++) {
      
      _data_buffer[_inv_cnt] = _data_bit[_register_size - (_inv_cnt + 1)];
      
    }
    
    for (int _trns_cnt = 0; _trns_cnt < _register_size; _trns_cnt++) {
      
      _data_bit[_trns_cnt] = _data_buffer[_trns_cnt];
      
    }
    
  }
  
  // Communication with shift register
  
  digitalWrite (_oe_pin, HIGH);
  digitalWrite (_oe_pin, LOW);
  
  for (int _wrt_cnt = 0; _wrt_cnt < _register_size; _wrt_cnt++) {
    
    digitalWrite (_data_pin, _data_bit[_wrt_cnt]);
    digitalWrite (_clock_pin, HIGH);
    digitalWrite (_clock_pin, LOW);
    
  }
  
  digitalWrite (_data_pin, LOW);
  
  digitalWrite (_oe_pin, HIGH);
  digitalWrite (_oe_pin, LOW);
  
}
