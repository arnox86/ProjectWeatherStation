
/*
*    Program shows how to operate a LCD panel with an shift register
*/


#include <shiftReg.h>    // Including shiftReg 


#define bright_pin 10    // Pin definitions
#define enable_pin 9

#define ON = 0xFF
#define OFF = 0b00000000

#define brightness  150  // Brightness of the display


bool brght_set = 0;    // Indicator if brightness is set

byte in_data;    // Data thats inside now


shiftReg sr (13, 12, 11, 0);



void set (boolean RS, byte data) {

  byte data1 = 0;
  byte data2 = 0;
  
  if (RS == 1) {
    
    bitSet (data1, 4);
    bitSet (data2, 4);
    
  }
  
  for (int bit_cnt = 0; bit_cnt < 4; bit_cnt++) {
    
    if ((data >> (4 + bit_cnt)) == 1) {
      
      bitSet (data1, bit_cnt);
      
    }
    
    if ((data >> bit_cnt) == 1) {
      
      bitSet (data2, bit_cnt);
      
    }
    
  }
  
  
  digitalWrite (enable_pin, HIGH);
  
  sr.shiftData (data1);
  
  digitalWrite (enable_pin, LOW);
  
  delayMicroseconds (1);
  
  digitalWrite (enable_pin, HIGH);
  
  sr.shiftData (data2);
  
  digitalWrite (enable_pin, LOW);
  
  delayMicroseconds (1);
  
}


void setup () {
  
  Serial.begin (9600);
  
  pinMode (enable_pin, OUTPUT);
  pinMode (bright_pin, OUTPUT);
  
  digitalWrite (enable_pin, LOW);
  digitalWrite (bright_pin, LOW);
  
}


void loop () {
  
  
  if (brght_set == 0) {
    
    for (int brght_cnt = 0; brght_cnt < brightness; brght_cnt++) {
      
      analogWrite (bright_pin, brght_cnt);
      delay (50);
      
    }
    
    brght_set = 1;
    
  }
  
  set (0, 0b00101000);    // Intializing
  delayMicroseconds (10000);
  
  set (0, 0b00001111);    // Cusor on
  delayMicroseconds (1);
 
  set (0, 0b00010100);    // Cursor right
  delayMicroseconds (1);
  
  delay (1000);
  
  set (0, 0b00010000);    // Cursor left
  delayMicroseconds (1);
  
  set (1, 0b11111111);
  delay (10000000);
  
  sr.shiftData (0b10101010);
  delay (10000000);
  
  exit (0);
  
}
