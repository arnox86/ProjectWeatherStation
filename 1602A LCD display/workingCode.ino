
/*
*    Program shows how to operate a LCD panel with an shift register
*/


#include <shiftReg.h>    // Including shiftReg 


#define bright_pin 10    // Pin definitions
#define enable_pin 9

#define brightness  150  // Brightness of the display


bool brght_set = 0;    // Indicator if brightness is set

byte in_data;    // Data thats inside now


shiftReg sr (13, 11, 12, 1);


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
      delay (1);
      
    }
    
    brght_set = 1;
    
  }

  digitalWrite (enable_pin, 1);   // Set to 4 bit operation mode
  delayMicroseconds (1);
  sr.shiftData (0b01000000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  sr.allZero();

  digitalWrite (enable_pin, 1);   
  delayMicroseconds (1);
  sr.shiftData (0b00010000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  delay (2);
  sr.allZero();
  Serial.println ("4 bit operation mode set");
  

  digitalWrite (enable_pin, 1);   // Setting cusor on
  delayMicroseconds (1);
  sr.shiftData (0b00000000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  sr.allZero();

  digitalWrite (enable_pin, 1);   
  delayMicroseconds (1);
  sr.shiftData (0b11110000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  delay (2);
  sr.allZero();
  Serial.println ("Cursor on");

  
  digitalWrite (enable_pin, 1);   // Display off
  delayMicroseconds (1);
  sr.shiftData (0b00000000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  sr.allZero();

  digitalWrite (enable_pin, 1);   
  delayMicroseconds (1);
  sr.shiftData (0b00010000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  sr.allZero();
  delay (1000);
  Serial.println ("Display off");


  digitalWrite (enable_pin, 1);   // Display on
  delayMicroseconds (1);
  sr.shiftData (0b00000000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  sr.allZero();

  digitalWrite (enable_pin, 1);   
  delayMicroseconds (1);
  sr.shiftData (0b11110000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  sr.allZero();
  delay (1000);
  Serial.println ("Display on");


  digitalWrite (enable_pin, 1);   // Entry mode set
  sr.shiftData (0b00100000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);

  digitalWrite (enable_pin, 1);   
  sr.shiftData (0b01100000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  delay (2);
  sr.allZero();
  Serial.println ("Entry mode set");


  digitalWrite (enable_pin, 1);   // Return home
  sr.shiftData (0b00000000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);

  digitalWrite (enable_pin, 1);   
  sr.shiftData (0b01000000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  delay (2);
  sr.allZero();
  Serial.println ("Return home");
  delay (1000);
  

for (int r_cnt = 0; r_cnt < 4; r_cnt++) {
  
  digitalWrite (enable_pin, 1);
  delayMicroseconds (1);
  sr.shiftData (0b10000000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  sr.allZero();

  digitalWrite (enable_pin, 1);
  delayMicroseconds (1);
  sr.shiftData (0b00100000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  sr.allZero();
  Serial.println ("Cursor right");
  delay (500);

}


  /*digitalWrite (enable_pin, 1);   // CGRAM adress 01h
  delayMicroseconds (1);
  sr.shiftData (0b00100000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);

  digitalWrite (enable_pin, 1);   
  delayMicroseconds (1);
  sr.shiftData (0b10000000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  delay (2);
  sr.allZero();
  Serial.println ("CGRAM adress 01h");
  delay (10);*/


  digitalWrite (enable_pin, 1);   // DDRAM adress 04h
  delayMicroseconds (1);
  sr.shiftData (0b00010000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);

  digitalWrite (enable_pin, 1);   
  delayMicroseconds (1);
  sr.shiftData (0b00100000);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  delay (2);
  sr.allZero();
  Serial.println ("DDRAM adress 04h");
  delay (10);


  delayMicroseconds (1);
  sr.shiftData (0b00001000);
  delayMicroseconds (1);
  digitalWrite (enable_pin, 1);   // Setting A to 04h
  delayMicroseconds (1);
  sr.shiftData (0b00101000);
  delayMicroseconds (1);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (1);
  sr.shiftData (0b00001000);
  delayMicroseconds (1);
  digitalWrite (enable_pin, 0);

  delayMicroseconds (1);
  sr.shiftData (0b00001000);
  delayMicroseconds (1);
  digitalWrite (enable_pin, 1); 
  delayMicroseconds (1);
  sr.shiftData (0b10001000);
  delayMicroseconds (1);
  digitalWrite (enable_pin, 0);
  delayMicroseconds (20);
  Serial.println ("Set 'A'");
  

  sr.allZero();

  delay (100);
  exit (0);
  
}
