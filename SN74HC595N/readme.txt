
Standard shift register library, but optimized for big programs.

Maximum register size is 128 bits.


Should be compatible to most other shift registers similar to the SN74HC595N.


Constructor: shiftReg /name/ (/data pin/, /clock pin/, /output enable pin aka latchpin/, /size of rgister in bytes/, \
                                  /most significant (1) of least significant (0) bit first/);

/name/.shiftData (/data for shift register/);   //Writes data into shift register

/name/.readOut (/Byte number you want to read/);    // Gives out one data byte

/name/.allOne ();   // Sets all pins to 1
/name/.allZero ();  // Sets all pins to 0
