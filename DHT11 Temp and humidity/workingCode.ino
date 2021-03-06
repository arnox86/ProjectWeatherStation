
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
*   Working code for reading out the DHT11, no libraries needed.
*/

#define com_pin 14

int data_out[5];
double output_hum, output_temp;


// Read out one 8-bit data pack

byte measure_run () {
  
  byte input_value;
  int count;
  
  for (count = 0; count < 8; count++) {
    
    // Wait until the next bit comes
    while (digitalRead(com_pin) != 1);
    
    // Wait 50us, if its HIGH, it is a 1, if its only 30us long HIGH,
    //  its a 0
    delayMicroseconds (50);
    
    if (digitalRead(com_pin) == 1) {
      
      // If its a 1 the bit gets a 1, else it stays a 0
      bitSet (input_value, 7-count);
      
      // Wait until the transmittion is ready
      while (digitalRead(com_pin) == 1);
      
    }
    
  }
  
  return (input_value);
  
}


void setup() {

  Serial.begin (9600);
  
  // The communication pin has to be HIGH to start communication
  
  pinMode (com_pin, OUTPUT);
  digitalWrite (com_pin, HIGH);

}


void loop() {
  
  digitalWrite (com_pin, HIGH);
  
  delay (1000);
  
  // Wakeup call:
 
  digitalWrite (com_pin, LOW);
  delay (18);
  
  digitalWrite (com_pin, HIGH);
  delayMicroseconds (1);
  
  
  pinMode (com_pin, INPUT);
  
  // DHT11 pushes voltage down after the wakeup call
  
  delayMicroseconds (45);
  
  // Error, if the first pull-down of the DHT11 is not detected
  
  if (digitalRead (com_pin) != 0) {
   
     Serial.println ("Error: 1");
     return;
    
  }
  
  delayMicroseconds (80);
  
  // Error, if the first pull-up of the DHT11 is not detected
  
  if (digitalRead (com_pin) != 1) {
    
    Serial.println ("Error: 2");
    return;
    
  }
  
  delayMicroseconds (80);
  
  // DHT11 start with the data transmittion
  
  // Read out the sensor data:
  
  int measure_counter;
  
  for (measure_counter = 0; measure_counter < 5; measure_counter++) {
    
    data_out[measure_counter] = measure_run();
    
  }
  
  delayMicroseconds (70);
  
  pinMode (com_pin, OUTPUT);
  digitalWrite (com_pin, HIGH);
  
  //for (int a = 0; a < 5; a++) Serial.println(data_out[a]);
  
  // Add integral and decimal data:
  
  output_hum = data_out[1];
  output_hum /= 10;
  output_hum += data_out[0];
  
  output_temp = data_out[3];
  output_temp /= 10;
  output_temp += data_out[2];
  
  Serial.print ("Humidity:    ");
  Serial.print (output_hum,1);
  Serial.println (" %");
  
  Serial.print ("Temperature: ");
  Serial.print (output_temp,1);
  Serial.println (" C");
  
  
  delay (500);
  exit (0);
  
}
