
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
*   dht11 /choose a name/ (/put here the number of your communication pi connected to the dht11/);
*
*   ...
*
*   void loop() {
*       name.measure();
*       double a = name.temp();     // Get temperature
*       double b = name.hum();      // Get humidity
*   }
*/

#ifndef dht11_h
#define dht11_h

#include "Arduino.h"


class dht11 {
  
  public:
    dht11(int pin);
    int measure();     // int only for debugging
    double temp();
    double hum();
  
  private:
    char _type;
    int _com_pin;
    int _data_out[5];
    double _output_temp;
    double _output_hum;
  
    byte _measure_run();
  
};

#endif
