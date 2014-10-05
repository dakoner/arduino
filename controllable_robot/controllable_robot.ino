#include <stdlib.h>
#include <NewPing.h>

#define TRIGGER_PIN  16
#define ECHO_PIN     17
#define MAX_DISTANCE 200

NewPing DistanceSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5);

void setup()
{
  Serial.begin(57600);
  mySerial.begin(9600);
  Serial.println("Do it.");
  /*
  // //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  // //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel B pin

  digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
  digitalWrite(8, HIGH);   //Disengage the Brake for Channel B
  */
}

void handleCommand(String curstring) {
/*
  unsigned int cm = DistanceSensor.ping_cm();
  Serial.print("DISTANCE: ");
  Serial.print(cm);
  Serial.println("cm");
*/

/*
  Serial.print("COMMAND: ");
  Serial.print("'");
  Serial.print(curstring);
  Serial.println("'");
*/
  String cmd = curstring.substring(0, 3);
  String num = curstring.substring(3);
  int rc = num.toInt();

  Serial.print("cmd: ");
  Serial.print(cmd);
  Serial.print(" num: ");
  Serial.println(num);


  if (rc == 0) { // stop
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
        analogWrite(3, 0);  
        analogWrite(11, 0);  

  } else {

    if (cmd == "fwd") {
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    }
    else if (cmd ==  "bck") {
      digitalWrite(12, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (cmd ==  "rgt") {
      digitalWrite(12, HIGH);
      digitalWrite(12, LOW);
    }

    else if (cmd == "lft") {
      digitalWrite(12, LOW);
      digitalWrite(12, HIGH);
    }



    digitalWrite(9, LOW); 
    analogWrite(3, rc);  

    digitalWrite(8, LOW);  
    analogWrite(11, rc);    

    delay(10);
  }
}

String readString = "";
void loop()
{
  while (mySerial.available()) {
    char c = mySerial.read();  //gets one byte from serial buffer
    if (c == '\n') {
       handleCommand(readString);
      readString = "";
    } else {
      readString += c; //makes the string readString
    }
  }
}

