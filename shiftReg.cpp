
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

  digitalWrite (_latch_pin, LOW);

  if (_MSB) {

    shiftOut (_data_pin, _clock_pin, LSBFIRST, _shift_data);

  }
  else {

    shiftOut (_data_pin, _clock_pin, MSBFIRST, _shift_data);

  }
  
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
