#include <Esplora.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  while (!Serial); // needed for Leonardo-based board like Esplora
  Serial.begin(57600);
  Serial1.begin(57600);
}

void loop() {
  if (Serial1.available())
     Serial.write(Serial1.read());
  
  
  delay(0.1);

}


