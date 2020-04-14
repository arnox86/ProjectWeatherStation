
/*
 *  Standard shift register library 
 *
 *  Program counts down from 255 to 0 and shows the binary output at the shift register LSB
 */

 
// Connections to the shift register
#define data_pin 14   // Data pin
#define clock_pin 15   // Clock pin
#define latch_pin    // Storage register clock pin


int data = 0xFF;   // Data for the output 
int data_size = 8;  // Size of the data in bits


void setup() {

  Serial.begin (9600);

  pinMode (data_pin, OUTPUT);
  pinMode (clock_pin, OUTPUT);

}


void loop() {

  boolean _data_bit[data_size];

  for (; data > 0; data--) {    // Counting the data down

    

    for (int _bit_count = 0; _bit_count < data_size; _bit_count++) {

      if (((data >> (data_size - (_bit_count + 1))) & 1) != 0) {
        
        _data_bit[_bit_count] = 1;
        Serial.print ("1");
        
      }
      else {
        
        _data_bit[_bit_count] = 0;
        Serial.print ("0");
        
      }
      
    }


    for (int _shift_clock = 0; _shift_clock < data_size; _shift_clock++) {

      digitalWrite (data_pin, _data_bit[_shift_clock]);
      digitalWrite (clock_pin, HIGH);
      digitalWrite (clock_pin, LOW);
    
    }

    Serial.println ("");

    delay (400);

  }

}
