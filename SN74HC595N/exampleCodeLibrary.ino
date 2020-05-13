
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
