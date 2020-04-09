
#include <dht11.h>
// #include "dht11.h"   // Use this one if your library is saved in the sketch folder


dht11 DHT11 (14);       // Put your communication pin in here; 14 is analog pin 0 at Arduino Uno

void setup () {
  
  Serial.begin (9600);  // Put your serial baud rate in here
  
}

void loop () {
  
  Serial.println (DHT11.temp());
  Serial.println (DHT11.hum());
  delay (500);
  
  exit (0);
  
}
