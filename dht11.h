
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
