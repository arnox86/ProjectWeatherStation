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

#ifndef dht11_h
#define dht11_h

#include "Arduino.h"

  /* Uncomment to get out the checksum */
//#define DEBUG_MESSAGE

#define DEBUG_BEGIN Serial

// Not really used, but standard in my libs:
#ifndef DEBUG_MESSAGE
  #define DEBUG_PRINT (...) { DEBUG_BEGIN.print (__VA_ARGS__); }
  #define DEBUG_PRINTLN (...) { DEBUG_BEGIN.println (__VA_ARGS); }

#else
  #define DEBUG_PRINT (...) {}    // Only placeholder if disabled
  #define DEBUG-PRINTLN (...) {}

#endif


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
