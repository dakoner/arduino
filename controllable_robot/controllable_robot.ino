#include <NewPing.h>

#define TRIGGER_PIN  16
#define ECHO_PIN     17
#define MAX_DISTANCE 200

NewPing DistanceSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
  Serial.begin(57600);
  Serial.println("Do it.");
  // //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  // //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel B pin

  digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
  digitalWrite(8, HIGH);   //Disengage the Brake for Channel B

}

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void loop()
{
  // Always print telemetry

  unsigned int cm = DistanceSensor.ping_cm();
  Serial.print("DISTANCE: ");
  Serial.print(cm);
  Serial.println("cm");
  // print the string when a newline arrives:
  if (stringComplete) {
    String curstring = inputString;
    inputString = "";
    stringComplete = false;

    // clear the string:
    Serial.println();
    Serial.print("COMMAND: ");
    Serial.print("'");
    Serial.print(curstring);
    Serial.println("'");
    if (curstring.startsWith("STOP")) {
      Serial.println("Stopping.");
      digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
      digitalWrite(8, HIGH);   //Disengage the Brake for Channel B
      analogWrite(3, 0);   //Spins the motor on Channel A at full speed
      analogWrite(11, 0);    //Spins

      return;
    }
    int firstCommandEnd = curstring.indexOf(" ");
    String firstCommand = curstring.substring(0, firstCommandEnd);
    Serial.print("first command: ");
    Serial.println(firstCommand);


    int secondCommandEnd = curstring.indexOf(" ", firstCommandEnd + 1);
    String secondCommand = curstring.substring(firstCommandEnd + 1, secondCommandEnd);
    Serial.print("second command: ");
    Serial.println(secondCommand);

    int thirdCommandEnd = curstring.indexOf(" ", secondCommandEnd + 1);
    String thirdCommand = curstring.substring(secondCommandEnd + 1, thirdCommandEnd);
    Serial.print("third command: ");
    Serial.println(thirdCommand);

    String fourthCommand = curstring.substring(thirdCommandEnd + 1, curstring.length());
    Serial.print("fourth command: ");
    Serial.println(fourthCommand);



    if (firstCommand == "FORWARD")
      digitalWrite(12, LOW); //Establishes backward direction of Channel A
    else if (firstCommand ==   "BACKWARD")
      digitalWrite(12, HIGH); //Establishes backward direction of Channel A
    else {
      Serial.println("Don't recgonize first command");

      return;
    }

    if (thirdCommand == "FORWARD")
      digitalWrite(13, LOW); //Establishes backward direction of Channel A
    else if (thirdCommand ==   "BACKWARD")
      digitalWrite(13, HIGH); //Establishes backward direction of Channel A
    else {
      Serial.println("Don't recgonize second command");

      return;
    }



    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, secondCommand.toInt());   //Spins the motor on Channel A at full speed

    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, fourthCommand.toInt());    //Spins the motor on Channel B at half speed

  }
     delay(100);

}
/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\r') {
      stringComplete = true;
    }
  }
}
