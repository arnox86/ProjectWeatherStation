
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




#include <shiftReg.h>


shiftReg sr (9, 10, 11, 0);   // data pin , clock pin, latch pin, MSB (1) or LSB (0)

void setup () {
  
  ;
  
}


void loop () {
  
  sr.shiftData (0b10101010);    // Set an output
  delay (1);
  
  sr.allOne ();   // Set all output pins to 1
  delay (1);
  
  sr.allZero ();    // Set all output pins to 0
  delay (1);
  
  uint8_t shiftRegister_value = sr.readOut ();    // Give out data in the shift register
  delay (1);
  
  exit (0);
  
}
