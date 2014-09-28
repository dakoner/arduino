/*
arduino_output

Demonstrates the control of digital pins of an Arduino board running the
StandardFirmata firmware.  Clicking the squares toggles the corresponding
digital pin of the Arduino.  

To use:
* Using the Arduino software, upload the StandardFirmata example (located
  in Examples > Firmata > StandardFirmata) to your Arduino board.
* Run this sketch and look at the list of serial ports printed in the
  message area below. Note the index of the port corresponding to your
  Arduino board (the numbering starts at 0).  (Unless your Arduino board
  happens to be at index 0 in the list, the sketch probably won't work.
  Stop it and proceed with the instructions.)
* Modify the "arduino = new Arduino(...)" line below, changing the number
  in Arduino.list()[0] to the number corresponding to the serial port of
  your Arduino board.  Alternatively, you can replace Arduino.list()[0]
  with the name of the serial port, in double quotes, e.g. "COM5" on Windows
  or "/dev/tty.usbmodem621" on Mac.
* Run this sketch and click the squares to toggle the corresponding pin
  HIGH (5 volts) and LOW (0 volts).  (The leftmost square corresponds to pin
  13, as if the Arduino board were held with the logo upright.)
  
For more information, see: http://playground.arduino.cc/Interfacing/Processing
*/

import processing.serial.*;

import cc.arduino.*;

Arduino arduino;



// Example 5-5: Button as switch
boolean button = false;
boolean button1 = false;

int x = 25;
int y = 25;
int w = 25;
int h = 25;

int x1 = 75;
int y1 = 25;

void setup() {
  size(200,200); 
  arduino = new Arduino(this, Arduino.list()[0], 57600);
    
  arduino.pinMode(12, Arduino.OUTPUT);
  arduino.pinMode(9, Arduino.OUTPUT);
  
  arduino.pinMode(13, Arduino.OUTPUT);
  arduino.pinMode(8, Arduino.OUTPUT);
  
}

// When the mouse is pressed, the state of the button is toggled.   
// Try moving this code to draw() like in the rollover example.  What goes wrong?
void mousePressed() {
  if (mouseX > x && mouseX < x+w && mouseY > y && mouseY < y+h) {
    button = !button;
  } else if (mouseX > x1 && mouseX < x1+w && mouseY > y1 && mouseY < y1+h) {
    button1 = !button1;
  }    
}


void draw() {
  if (button) {
    stroke(0);
    fill(175);
  } else {
    stroke(255);
    fill(25);
  }
  rect(x,y,w,h);

  if (button1) {
    stroke(0);
    fill(175);
  } else {
    stroke(255);
    fill(25);
  }
  rect(x1,y1,w,h);
  
  
  if (button1) {
    arduino.digitalWrite(9, Arduino.HIGH);
    arduino.analogWrite(3, 0);

    arduino.digitalWrite(8, Arduino.HIGH);
    arduino.analogWrite(11, 0);
  } else if (button) {
    arduino.digitalWrite(12, Arduino.HIGH);
    arduino.digitalWrite(9, Arduino.LOW);
    arduino.analogWrite(3, 255);

    arduino.digitalWrite(13, Arduino.HIGH);
    arduino.digitalWrite(8, Arduino.LOW);
    arduino.analogWrite(11, 255);
  } 
}

