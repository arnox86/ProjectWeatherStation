
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
