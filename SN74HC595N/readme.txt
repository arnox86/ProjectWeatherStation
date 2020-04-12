
Standard shift register library, but optimized for big programs.

Maximum register size is 128 bits.


Should be compatible to most other shift registers similar to the SN74HC595N.


Constructor: shiftReg /name/ (/data pin/, /clock pin/, /output enable pin/, /size of rgister/, \
                                  /most significant (1) of least significant (0) bit first/);

/name/.shift (/data for shift register/);
