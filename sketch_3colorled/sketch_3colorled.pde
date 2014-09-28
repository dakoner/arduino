import processing.serial.*;
import cc.arduino.*;

OPC opc;

Arduino arduino; //creates arduino object

color back = color(0); //variables for the 2 colors

int width = 1024;
int height = 512;

int sensor= 0;
int sensor2= 1;
int sensor3 = 2;

int read;
int read2;
int read3;


int padheight = 30;
int padwidth = 10;


void setup() {
  size(width, height);
  frame.setLocation(0, 0);
  arduino = new Arduino(this, Arduino.list()[0], 57600); //sets up arduino
  arduino.pinMode(sensor, Arduino.INPUT);//setup pins to be input (A0 =0?)
  arduino.pinMode(sensor2, Arduino.INPUT);//setup pins to be input (A0 =0?)
  arduino.pinMode(sensor3, Arduino.INPUT);//setup pins to be input (A0 =0?)


  // Connect to the local instance of fcserver. You can change this line to connect to another computer's fcserver
  opc = new OPC(this, "127.0.0.1", 7890);
  opc.setPixel(0, color(255, 255, 255));
  opc.writePixels();

  background(back);
}

void draw() {
 
 
  read=arduino.analogRead(sensor);
  read2=arduino.analogRead(sensor2);
  read3=arduino.analogRead(sensor3);

  background(back);
  
  int value = int(map(read, 0, 1023, 0, 255));
  int value2 = int(map(read2, 0, 1023, 0, 255));
  int value3 = int(map(read3, 0, 1023, 0, 255));
  fill(value, value2, value3);
  rect(0, 0, width, height);
  opc.setPixel(0, color(value, value2, value3));
  opc.writePixels();
  


}

