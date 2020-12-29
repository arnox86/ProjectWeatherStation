
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




#include <dht11.h>
// #include "dht11.h"   // Use this one if your library is saved in the sketch folder


dht11 DHT11 (14);       // Put your communication pin in here; 14 is analog pin 0 at Arduino Uno

void setup () {
  
  Serial.begin (9600);  // Put your serial baud rate in here
  
}

void loop () {
  
  DHT11.measure();      // Doing one measurement
  
  Serial.print ("Temperature: ");
  Serial.print (DHT11.temp(),1);  // Giving out the temperature
  Serial.println (" C");
  
  Serial.print ("Humidity:    ");
  Serial.print (DHT11.hum(),1);  // Giving out the humidity
  Serial.println (" %");
  
  delay (500);
  
  exit (0);
  
}
