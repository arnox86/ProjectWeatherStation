/*
*
*   Direct data for .update function is in binput; structure: bits 0-7: data bits 0-7; bit 8: rs pin enabled or not;
*
*   The program has 4 diffrent operation mode configurations:
*     # Has to be initialized by using .initShiftRegister():
*       - shift register in 8 bit mode: rs and enable pins have to be seperate
*       - shift register in 4 bit mode
*     # Set by default (bit mode has to be configured anyway in constructor)
*       - direct pins in 8 bit mode: all data pins and rs/enable need own pins at Arduino
*       - direct pins in 4 bit mode
*
*/


#include "Arduino.h"
#include "1602A.h"

#include "shiftReg.h"


1602A::1602A (pin_input[0], pin_input[1], pin_input[2], pin_input[3], pin_input[4], pin_input[5], pin_input[6], pin_input[7], 
              uint16_t enable_pin, uint16_t rs_pin, uint16_t bright_pin, uint16_t brightness, 
              uint8_t operation_mode) {
  
  _sr_init = 0;   // 0 by default
  
  for (uint8_t _piv = 0; _piv < 8; _piv++) {
    
    _dataPin[_piv] = pin_input[_piv];   // Putting data pins to private variables
    
  }
  
  pinMode (bright_pin, OUTPUT);
  
  for (uint8_t brtcnt = 0; brtcnt < brightness; brtcnt++) {
    
    analogWrite (bright_pin, brtcnt);   // Slowly increasing brightness
    delay (1);
    
  }
  
  analogWrite (bright_pin, brightness);   // Setting brightness to final value
  
  if (operation_mode == 8) _8bit_mode = 1;
  else if (operation_mode == 4) _8bit_mode = 0;   // Operation mode indication for following program
  else {
    
    OUT_TYPE.print ("operation mode failure: bus mode not available; input: ");   // Debug message
    OUT_TYPE.println (operation_mode);
    return;
    
  }
  
}


void 1602A::initShiftRegister (uint16_t data_pin, uint16_t clock_pin, uint16_t latch_pin) {
  
  shiftReg sr_lcd (data_pin, clock_pin, latch_pin, 1);    // 1 for MSB first
  
  sr_lcd.allZero();   // Setting all pins to 0 to prevent from overheat
  
  _sr_init = 1;   // Shift register is used
  
  
}


void 1602A::update (uint16_t binput) {
  
  
  if (_sr_init == 1) {    
    
    
    _sr_output = OFF;   // Setting output to 0 to prevent errors
    
    
    if (_8bit_mode == 1) {    // 8 bit operation mode
    
      for (uint16_t assntcnt = 0; assntcnt < 8; assntcnt++) {   // Putting right pin order into _sr_assignment
      
        _dbuffer[0] = _dataPin[assntcnt];
        
        _sr_assignment[_dbuffer[0]] = _dataPin[assntcnt];
      
      }
    
      for (uint16_t bscnt = 0; bscnt < 8; bscnt++) {  // Setting data into shift register byte
      
        _andbuffer = 0;
      
        bitSet (_andbuffer, bscnt);   // Setting bit to read to 1
      
        if ((binput & _andbuffer) != 0) {
        
          bitSet (_sr_output, 7 - _sr_assignment[bscnt]);   // Input has to be inverted for shift register
        
        }
        else;
      
      }
    
      _andbuffer = 0;
      bitSet (_andbuffer, 8);
   
      if ((binput & _andbuffer) != 0) {
      
        _rs_state = 1;
      
      }
      
    
      pinMode (enablePin, OUTPUT);    // Setting pins to output, shift register can not be used
      pinMode (rs_pin, OUTPUT);
    
      sr_lcd.allZero();   // Setting shift register to 0
      digitalWrite (enablePin, HIGH);   // Setting enable pin to high: indicator for data transmittion
      delayMicroseconds (1);
      
      digitalWrite (rs_pin, _rs_state);   // 1 if data is written to the ddram
      sr_lcd.shiftData (_sr_output);
      
      delayMicroseconds (1);
    
    }
  
    
    
  }
  
}


void 1602A::write (uint16_t x_axis, uint16_t y_axis, uint8_t b_input) {
  
  // IMPLEMENTATION OF AXIS (ram)
  
  
}

