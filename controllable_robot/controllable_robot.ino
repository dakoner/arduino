#include <stdlib.h>
#include <NewPing.h>

#define TRIGGER_PIN  16
#define ECHO_PIN     17
#define MAX_DISTANCE 200

NewPing DistanceSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5);

unsigned long time_since_command = 0;
unsigned long last_time;

bool inactive = true;

void setup()
{
  Serial.begin(57600);
  mySerial.begin(9600);
  Serial.println("Do it.");

  // //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  // //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel B pin

  last_time = millis();
}

void set_speed() {
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(3, 255);    //Spins the motor on Channel A at half speed
  analogWrite(11, 255);   //Spins the motor on Channel B at full speed
}

void loop()
{
  if (mySerial.available()) {
    char c = mySerial.read();
    Serial.print("chr:");
    Serial.println(c);
    switch (c) {
      case 'f':
        digitalWrite(12, LOW); //Establishes forward direction of Channel A
        digitalWrite(13, LOW); //Establishes forward direction of Channel B
        set_speed();
        break;
      case 'b':
        digitalWrite(12, HIGH); //Establishes forward direction of Channel A
        digitalWrite(13, HIGH); //Establishes forward direction of Channel B
        set_speed();
        break;
      case 'r':
        digitalWrite(12, LOW); //Establishes forward direction of Channel A
        digitalWrite(13, HIGH); //Establishes forward direction of Channel B
        set_speed();
        break;
      case 'l':
        digitalWrite(12, HIGH); //Establishes forward direction of Channel A
        digitalWrite(13, LOW); //Establishes forward direction of Channel B
        set_speed();
        break;
      case 's':
        digitalWrite(9, HIGH);
        digitalWrite(8, HIGH);
        analogWrite(3, 0);
        analogWrite(11, 0);
        break;
    }

    last_time = millis();
    time_since_command = 0;
    inactive = false;
  } else {
    Serial.print(last_time);
    Serial.print(" ");
    Serial.println(time_since_command);
    unsigned long dt = millis() - last_time;
    time_since_command += dt;
    if (time_since_command > 1000 && !inactive) {
      Serial.println("disable motor");
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);
      analogWrite(3, 0);
      analogWrite(11, 0);
      inactive = true;
    }
  }
}
