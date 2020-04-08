
#include "Arduino.h"
#include "dht11.h"


dht11::dht11(int pin) {
  
  _com_pin = pin;
  pinMode (_com_pin, OUTPUT);
  digitalWrite (_com_pin, HIGH);
  
}
