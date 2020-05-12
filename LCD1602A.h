/*
*
*/


#ifndef LCD1602A_h
#define LCD1602A_h

#include "Arduino.h"
#include "shiftReg.h"


#ifndef SH_REG

  #ifndef SHIFT_REGISTER_INDICATOR
    #define SH_REG 0

  #else
    #define SH_REG 1

  #endif
#endif


#ifndef OUT_TYPE
  #define OUT_TYPE Serial    // Output type
#endif


#ifndef ON
  #define ON 0xFF
#endif

#ifndef OFF
  #define OFF 0b00000000    // Just to be sure ;)
#endif

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02    // Setting DDRAM adress to 0
#define ENTRY_MODE 0x04   // Cursor and display shift
#define DISPLAY_STATE 0x08    // Display on or off
#define CURSOR_STATE 0x10   // Cursor settings without influencing DDRAM
#define FUNCTION_SET 0x20   // Intializing line and data bus mode
#define CGRAM_SET 0x40    // Setiing CGRAM adress
#define DDRAM_SET 0x80    // Setting DDRAM adress


class LCD1602A {
  
  public:
    uint16_t pin_input[8];
  
    LCD1602A (pin_input[0], pin_input[1], pin_input[2], pin_input[3], pin_input[4], pin_input[5], pin_input[6], pin_input[7], uint16_t enable_pin, uint16_t rs_pin, uint16_t bright_pin, uint16_t brightness, uint8_t operation_mode);
  
    void initShiftRegister (uint16_t data_pin, uint16_t clock_pin, uint16_t latch_pin);
  
    void initLCD ();
  
    void update (uint16_t binput);   // Order of binput bits: 7-0 data; 8 rs;
  
    void write (uint16_t x_axis, uint16_t y_axis, uint8_t dec_input);
    
  
  private:
    uint16_t _dataPin[10];    // Private variable for data pins
    uint16_t _pbuffer[10];
    uint16_t _dbuffer[10];   // Random data buffer
    
    uint16_t _andbuffer;      // Buffer to put bit into right order (.update)
    
    uint8_t _sr_assignment[8];    // Assignment of output and output pins at shift register
    uint8_t _sr_output;   // Output byte for shift register
  
    bool _sr_init;    // Indicates if shift register is used, 0 by default
    bool _8bit_mode;    // Operation mode: 1 = 8 bit, 0 = 4 bit
    bool _rs_state;    // State of rs pin
    bool _rs_srUse;   // Indicates usage of shift register for rs pin
    bool _enable_srUse;   // Same with enable pin
    
};


#endif
