/*
  Processing Simple Remote
 
 This sketch lets you read or write to all the Esplora's inputs or outputs
 
 You can type one of the following commands (without quotes) to get an answer:
 
 "D": prints the current value of all sensors.
 
 "Rxxx"
 "Gxxx"
 "Bxxx": set the color of the RGB led. For example, write "R255"
 to turn on the red to full brightness, "G128" to turn
 the green to half brightness, or "G0" to turn off
 the green channel.
 
 "Txxxx": play a tone with the piezo. The number is the
 frequency, e.g. "T440" plays  middle A.
 Write "T0" to turn off the piezo.
 
 created 22 Dec 2012
 by Tom Igoe
 
 This example is in the public domain.
 */

import processing.serial.*;        // initialize the serial library

Serial Esplora;                    // the Esplora's serial port connection
String numberString = "";          // string of the next port to be initialized
String[] valueNames = {            // names associated with the values the Esplora will send
  "switch 1", "switch 2", "switch 3", "switch 4", "slider", 
  "light sensor", "temperature (Celsius)", "microphone", "joystick switch", 
  "joystick X", "joystick Y", "accelerometer X axis", "accelerometer Y axis", 
  "accelerometer Z axis"
};
String displayString = "";         // string to display info onscreen
char command;                      // single-letter command from the user

void setup() {
  size(640, 480);  // Stage size
}

void draw() {
  // clear the screen:
  background(0);
  fill(255);
  int linePosition = 20;        // set the initial text line position:

  // if there's not an Esplora initialized:
  if (Esplora == null) {
    // get a list of the serial ports:
    String[] portList = Serial.list();
    // draw instructions on the screen:
    text("Type P and the port number of your Esplora:", linePosition, 20);
    // draw the port list on the screen:
    for (int i = 0; i < portList.length; i++) {
      linePosition = (i+4) *20;
      text("port " + i + ":  " + portList[i], 20, linePosition);
    }
  } 

  // if you've got all the ports:
  else {
    // display latest news:
    text(displayString, 20, linePosition);

    // moe lower in the screen and print some updates:
    linePosition = 240;    
    text("type Rxxx (xxx = a number 0-255) and return to set the red value", 20, linePosition);
    linePosition += 20;
    text("type Gxxx (xxx = a number 0-255) and return to set the green value", 20, linePosition);
    linePosition += 20;
    text("type Bxxx (xxx = a number 0-255) and return to set the blue value", 20, linePosition);
    linePosition += 20;
    text("type Txxx (xxx = a number 0 - 20000) and return to set the tone", 20, linePosition);
    linePosition += 20;
    text("type D to get the values of all sensors", 20, linePosition);
  }
}

void serialEvent(Serial Esplora) {
  // read a String from the serial port:
  displayString = Esplora.readStringUntil('\n');
  // parse the response and add labels for display:
  displayString = parseResponse(displayString);
}

void keyReleased() {
  // letters A-Z and a-z might be commands:
  if (key >= 'A' && key <= 'z') {   
    command = key;
  }
  // if the enter key is pressed, stop looking for port number selections:
  if (key == ENTER ) {
    String outputString = "";
    switch (command) {
    case 'D':     // Dump values from Esplora
    case 'd': 
      outputString = "D" + numberString;
      break;
    case 'R':     // set red value (0 - 255)
    case 'r':
      outputString = "R" + numberString;
      break;
    case 'G':     // set green value (0 - 255)
    case 'g': 
      outputString = "G" + numberString;
      break;
    case 'B':     // set blue value (0 - 255)
    case 'b': 
      outputString = "B" + numberString;
      break;
    case 'T':     // set tone value (0 - 20000)
    case 't': 
      outputString = "T" + numberString;  
      break;
    case 'P':     // open serial port
    case 'p':
      if (Esplora == null) {
        choosePort(numberString);
        outputString = "Port " + numberString + " opened.";
      } 
      else {
        outputString = "Port already open";
      }
      break;
    }
    // update the display string with the latest from the user:
    displayString = outputString;
    // if there's something to write to the Esplora, send it:
    if (outputString != "") {
      Esplora.write(outputString);
      numberString = "";        // clear the number string
    }
    command = 0;                // clear the command value
  }
  // if the user types 0 though 9, use it as a port number selection:
  if (key >= '0' && key <= '9') {
    numberString += key;
  }
}

void choosePort(String thisPort) {
  int whichPort = int(thisPort);    // convers the string to an integer
  // if the number is value, open the port:
  if (whichPort >= 0 && whichPort < Serial.list().length) {
    // get the port name from the serial list:
    String portName = Serial.list()[whichPort];
    // initialize the next Esplora:
    Esplora = new Serial(this, portName, 9600);
    // read bytes into a buffer until you get a linefeed (ASCII 10):
    Esplora.bufferUntil('\n');
    // clear the string holding the port number:
    numberString = "";
  }
}

String parseResponse(String inputString) {
  String response = "";                           // a string to return from the function
  int[] values = int(split(inputString, ","));    // split the input string on the commas

  // loop over the input array, adding the labels from the valueNames array:
  for (int i = 0; i < values.length; i++) {
    response += (valueNames[i] + ": " + values[i] + "\n");
  }
  // return the resulting string:
  return response;
}

