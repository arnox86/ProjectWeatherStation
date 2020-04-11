/*
*   Usage:
*   
*   #include <dht11.h>
*
*   ...
*
*   dht11 /choose a name/ (/put here the number of your communication pi connected to the dht11/);
*
*   ...
*
*   void loop() {
*       name.measure();
*       double a = name.temp();     Getting temperature
*       double b = name.hum();      Getting humidity
*   }
*/



#include "Arduino.h"
#include "dht11.h"


dht11::dht11 (int pin) {
  
  _com_pin = pin;
  pinMode (_com_pin, OUTPUT);
  digitalWrite (_com_pin, HIGH);
  
}

int dht11::measure () {

  delay (1000);
  
  digitalWrite (_com_pin, LOW);
  delay (18);
  
  digitalWrite (_com_pin, HIGH);
  delayMicroseconds (1);
  
  
  pinMode (_com_pin, INPUT);
  delayMicroseconds (45);
  
  if (digitalRead (_com_pin)) return (1111);
  
  delayMicroseconds (80);
  
  if (!digitalRead (_com_pin)) return (2222);
  
  delayMicroseconds (80);
  
  
  byte _input_value;
  int count;
  
  for (int _measure_counter = 0; _measure_counter < 5; _measure_counter++) {
    
    _input_value = 0;
    
    for (count = 0; count < 8; count++) {
    
      // Wainting until the next bit comes
      while (digitalRead(_com_pin) != 1);
    
      // Waiting 50us, if its HIGH, it is a 1, if its only 30us long HIGH,
      //  its a 0
      delayMicroseconds (50);
    
      if (digitalRead(_com_pin) == 1) {
      
        // If its a 1 the bit gets a 1, else it stays a 0
        bitSet (_input_value, 7-count);
      
        // Waiting until the transmittion is ready
        while (digitalRead(_com_pin) == 1);
      
      }
    
    }
    
    _data_out[_measure_counter] = _input_value;
    
  }

  pinMode (_com_pin, OUTPUT);
  digitalWrite (_com_pin, HIGH);

  delay (500);
  
  
  // Giving out complete data if debug is enabled
  DEBUG_PRINTLN ("Data 0-3: ");
  
  for (int dbg = 0; dbg < 4; dbg++) {
    
    DEBUG_PRINTLN (_data_out[dbg]);
    
  }
  
  DEBUG_PRINTLN ("Checksum: ");
  DEBUG_PRINTLN (_data_out[4]);
  
  
  _output_hum = _data_out[1];
  _output_hum /= 10;
  _output_hum += _data_out[0];
  
  _output_temp = _data_out[3];
  _output_temp /= 10;
  _output_temp += _data_out[2];

}

double dht11::temp() {
  
  return (_output_temp);

}

double dht11::hum() {
  
  return (_output_hum);

}
