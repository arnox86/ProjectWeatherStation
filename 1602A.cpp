/*
*
*   Direct data for .update function is in binput; structure: bits 0-7: data bits 0-7; bit 8: rs pin enabled or not;
*     For activation of rs pin int _rs_state is set to 1.
*
*   The program has 4 different operation mode configurations:
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


void 1602A::initLCD () {
  
  
  
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
      
      digitalWrite (rs_pin, _rs_state);   // 1 if data is written to the DDRAM
      sr_lcd.shiftData (_sr_output);
      digitalWrite (enablePin, LOW);
      
      delayMicroseconds (1);    // Setting all to 0
      sr_lcd.allZero();
      digitalWrite (rs_pin, LOW);
      delayMicroseconds (1);
    
    }
  
    if (8bit_mode == 0) {
      
      for (uint16_t passcnt = 0; passcnt < 2; passcnt++) {
        
      if (passcnt == 0) {
      
        if (_dataPin[0] == 0 && rs_pin > 0) {
        
          pinMode (rs_pin, OUTPUT);
          _rs_srUse = 0;    // Indicator if shift register is used for rs pin
        
        }
        else if (_dataPin[0] > 0 && rs_pin == 0) {
        
          _rs_srUse = 1;
        
        }
        else {
        
          OUT_TYPE.println ("rs pin assignment failure");   // Wrong pin assignment at constructor
          return;
        
        }
      
        if (_dataPin[1] == 0 && enable_pin > 0) {
        
          pinMode (enable_pin, OUTPUT);
          _enable_srUse = 0;
        
        }
        else if (_dataPin[1] > 0 && enable_pin == 0) {
        
          _enable_srUse = 1;
        
        }
        else {
        
          OUT_TYPE.println ("enable pin assignment failure");   // Wrong pin assignment at constructor
          return;
          
        }
      
     
        for (uint16_t assntcnt = 0; assntcnt < 8; assntcnt++) {   // Putting right pin order into _sr_assignment
      
          _dbuffer[0] = _dataPin[assntcnt];
        
          _sr_assignment[_dbuffer[0]] = _dataPin[assntcnt];
      
        }
      
        for (uint16_t bscnt = 4; bscnt < 8; bscnt++) {
        
          _andbuffer = 0;
          bitSet (_andbuffer, bscnt);
        
          if ((binput & _andbuffer) != 0) {
          
            bitSet (_sr_output, 7 - _sr_assignment[bscnt]);
          
          }
        
        }
      
        if (_rs_state == 1 && _rs_srUse == 1) {
        
          bitSet (_sr_output, 7 - _sr_assignment[0]);
        
        }
        
      }
        
      if (passcnt == 1) {   // Second pass => data bits 3 - 0
        
        for (uint16_t bscnt = 0; bscnt < 4; bscnt++) {
        
          _andbuffer = 0;
          bitSet (_andbuffer, bscnt);
        
          if ((binput & _andbuffer) != 0) {
          
            bitSet (_sr_output, 7 - _sr_assignment[bscnt + 4]);
          
          }
          
        }
        
        if (_rs_state == 1 && _rs_srUse == 1) {
        
          bitSet (_sr_output, 7 - _sr_assignment[0]);
        
        }
        
      }
      
      
      sr_lcd.allZero();
      
      _andbuffer = 0;
      
      if (_enable_srUse == 1) {
        
        bitSet (_andbuffer, 7 - _sr_assignment[1]);   // For only setting enable pin
        bitSet (_sr_output, 7 - _sr_assignment[1]);
        
        sr_lcd.shiftData (_andbuffer);
        
      }
      else {
        
        digitalWrite (enable_pin, HIGH);
        
      }
      
      delayMicroseconds (1);
      
      if (_rs_srUse == 0) {
        
        digitalWrite (rs_pin, _rs_state);
        
      }
      
      sr_lcd.shiftData (_sr_output);
      
      if (_enable_srUse == 0) {
        
        digitalWrite (enable_pin, LOW);
        
      }
      if (_rs_srUse == 0) {
        
        digitalWrite (rs_pin, LOW);
        
      }
      
      delayMicroseconds (1);
      
      sr_lcd.allZero();
      
    }
      
    }   // passcnt
    
  }
  
  
  if (_sr_init == 0) {    // If no shift register is used
    
    pinMode (enable_pin, OUTPUT);
    pinMode (rs_pin, OUTPUT);
    
    
    if (_8bit_mode == 1) {
      
      for (uint16_t outsetcnt = 0; outsetcnt < 8; outsetcnt++) {
      
        pinMode (_dataPin[outstecnt], OUTPUT);
      
      }

      digitalWrite (enable_pin, HIGH);
      delayMicroseconds (1);
      
      _andbuffer = 0;
      bitSet (_andbuffer, 8);
      
      if ((_binput & _andbuffer) != 0) {
        
        digitalWrite (rs_pin, HIGH);
        
      }
      else {
        
        digitalWrite (rs_pin, LOW);
        
      }
      
      for (uint16_t andcnt = 0; andcnt < 8; andcnt++) {
        
        _andbuffer = 0;
        
        bitSet (_andbuffer, andcnt);    // Setting bit to read out binary input
        
        if ((_andbuffer & _binput) != 0) {
          
          digitalWrite (_dataPin[7 - andcnt], HIGH);    // Writing data onto pins
          
        }
        else {
          
          digitalWrite (_dataPin[7 - andcnt], LOW);
          
        }
        
      }
      
      delayMicroseconds (1);
      digitalWrite (enable_pin, LOW);
      
      for (uint16_t offcnt = 0; offcnt < 8; offcnt++) {
        
        digitalWrite (_dataPin[offcnt], LOW);   // Setting all pins to 0
        
      }
      
      digitalWrite (rs_pin, LOW);
      
    }
    
    
    if (_8bit_mode == 0) {
      
      for (uint16_t outcnt = 4; outcnt < 8; outcnt++) {
        
        pinMode (_dataPin[outcnt], OUTPUT);
        
      }
      
      _andbuffer = 0;
      
      for (uint16_t passcnt = 0; passcnt < 2; passcnt++) {
      
        if (passcnt == 0) {
          
          for (uint16_t lowcnt = 0; lowcnt < 8; lowcnt++) {
            
            digitalWrite (_dataPin, LOW);
            
          }
        
          digitalWrite (enable_pin, HIGH);
          delayMicroseconds (1);
          
          _andbuffer = 0; 
          bitSet (_andbuffer, 8);
          
          if ((_andbuffer & _binput) != 0) {
            
            digitalWrite (rs_pin, HIGH);
            
          }
          
          for (uint16_t andcnt = 4; andcnt < 8; andcnt++) {
        
            _andbuffer = 0;
        
            bitSet (_andbuffer, andcnt);
            
            if ((_andbuffer & _binput) != 0) {
              
              digitalWrite (_dataPin[andcnt], HIGH);
              
            }
                  
          }
          
          delayMicroseconds (1);
          
          digitalWrite (enable_pin, LOW);
          digitalWrite (rs_pin, LOW);
          
          for (uint16_t lowcnt = 0; lowcnt < 8; lowcnt++) {
            
            digitalWrite (_dataPin, LOW);
            
          }
        
        }
        
        if (passcnt == 1) {
          
          
          
        }
                  
      }
      
    }
    
  }
  
}


void 1602A::write (uint16_t x_axis, uint16_t y_axis, uint8_t b_input) {
  
  // IMPLEMENTATION OF AXIS (ram)
  
  
}

