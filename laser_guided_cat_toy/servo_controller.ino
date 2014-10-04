#include <Servo.h>

Servo servo1; Servo servo2; 


void setup() {
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  servo1.attach(14); //analog pin 0
  servo2.attach(15); //analog pin 1
  Serial.begin(9600);
  Serial.println("Ready");
  servo1.write(93);
  servo2.write(92);
}

void loop() {

  static int v = 0;

  if ( Serial.available()) {
    char ch = Serial.read();

    switch(ch) {
      case '0'...'9':
        v = v * 10 + ch - '0';
        break;
      case 's':
        Serial.println(v);
        servo1.write(v);
        v = 0;
        break;
      case 'w':
        Serial.println(v);
        servo2.write(v);
        v = 0;
        break;
    }
  }
} 


