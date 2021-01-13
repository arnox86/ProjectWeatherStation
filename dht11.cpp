
/*
MIT License

Copyright (c) 2020 Benedikt Bursian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/




/*
*   Usage:
*   
*   #include <dht11.h>
*
*   ...
*
*   dht11 /choose a name/ (/put here the number of your communication pin connected to the dht11/);
*
*   ...
*
*   void loop() {
*       name.measure();
*       double a = name.temp();     Get temperature
*       double b = name.hum();      Get humidity
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
  
  if (digitalRead (_com_pin)) {

    return (1111);
    
  }
  
  delayMicroseconds (80);
  
  if (!digitalRead (_com_pin)) {

    return (2222);
    
  }
  
  delayMicroseconds (80);
  
  
  byte _input_value;
  int _count;
  
  for (int _measure_counter = 0; _measure_counter < 5; _measure_counter++) {
    
    _input_value = 0;
    
    for (_count = 0; _count < 8; _count++) {
    
      // Wait until the next bit comes
      while (digitalRead(_com_pin) != 1);
    
      // Wait 50us, if its HIGH, it is a 1, if its only 30us long HIGH,
      //  its a 0
      delayMicroseconds (50);
    
      if (digitalRead(_com_pin) == 1) {
      
        // If its a 1 the bit gets a 1, else it stays a 0
        bitSet (_input_value, 7-_count);
      
        // Wait until the transmittion is ready
        while (digitalRead(_com_pin) == 1);
      
      }
    
    }
    
    _data_out[_measure_counter] = _input_value;
    
  }

  pinMode (_com_pin, OUTPUT);
  digitalWrite (_com_pin, HIGH);

  // Wait half a second so the DHT11 is ready for data transmitton again
  delay (500);
  
  
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
