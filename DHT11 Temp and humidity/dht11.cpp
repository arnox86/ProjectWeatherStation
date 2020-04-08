
#include "Arduino.h"
#include "dht11.h"


dht11::dht11 (int pin) {
  
  _com_pin = pin;
  pinMode (_com_pin, OUTPUT);
  digitalWrite (_com_pin, HIGH);
  
}

double dht11::measure (String out_type) {
  
  delay (50);
  
  digitalWrite (_com_pin, LOW);
  delay (18);
  
  digitalWrite (_com_pin, HIGH);
  delayMicroseconds (1);
  
  
  pinMode (_com_pin, INPUT);
  delayMicroseconds (45);
  
  if (!digitalRead (_com_pin)) return (1111);
  
  delayMicroseconds (80);
  
  if (digitalRead (_com_pin)) return (2222);
  
  delayMicroseconds (80);
  
  
  byte _input_value;
  int count;
  
  for (int _measure_counter = 0; _measure_counter < 5; _measure_counter++) {
    
    _input_value = 0;
    
    for (count = 0; count < 8; count++) {
    
      // Wainting until the next bit comes
      while (digitalRead(com_pin) != 1);
    
      // Waiting 50us, if its HIGH, it is a 1, if its only 30us long HIGH,
      //  its a 0
      delayMicroseconds (50);
    
      if (digitalRead(com_pin) == 1) {
      
        // If its a 1 the bit gets a 1, else it stays a 0
        bitSet (_input_value, 7-count);
      
        // Waiting until the transmittion is ready
        while (digitalRead(com_pin) == 1);
      
      }
    
    }
    
    _data_out[_measure_counter] = _input_value;
    
  }
  
  double _output_hum;
  double _output_temp;
  
  _output_hum = _data_out[1];
  _output_hum /= 10;
  _output_hum += _data_out[0];
  
  _output_temp = _data_out[3];
  _output_temp /= 10;
  _output_temp += _data_out[2];
  
  
  if (out_type = "hum") return (_output_hum);
  if (out_type = "temp") return (_output_temp);
  
}
