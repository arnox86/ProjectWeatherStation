/*
*   
*/

#ifndef dht11_h
#define dht11_h

#include "Arduino.h"

class dht11 {
  
  public:
    dht11(int pin);
    double measure(String out_type);
  
  private:
    int _com_pin;
    int _data_out[5];
    double _output;
  
    byte _measure_run();
  
};

#endif
