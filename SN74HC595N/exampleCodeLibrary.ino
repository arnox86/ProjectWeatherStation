
#include <shiftReg.h>


shiftReg reg1 (9, 10, 11, 8, 0);   // data pin , clock pin, output enable pin, size of register, MSB (1) or LSB (0)

void setup () {
}


void loop () {
  
  reg1.shift (0xFF);    // Set all outputs 1
  
  exit (0);
  
}
