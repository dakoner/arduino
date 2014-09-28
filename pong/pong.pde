import processing.serial.*;
import cc.arduino.*;

Arduino arduino; //creates arduino object

color back = color(0); //variables for the 2 colors

int width = 1024;
int height = 512;

int sensor= 0;
int sensor2= 1;

int read;
int read2;

float value;
float value2;

int padheight = 30;
int padwidth = 10;

int x;
int y;
int vx;
int vy;

int bx = 5;
int by = 5;

int p0score = 0;
int p1score = 0;

void setup() {
  size(width, height);
  frame.setLocation(0, 0);
  arduino = new Arduino(this, Arduino.list()[0], 57600); //sets up arduino
  arduino.pinMode(sensor, Arduino.INPUT);//setup pins to be input (A0 =0?)
  arduino.pinMode(sensor2, Arduino.INPUT);//setup pins to be input (A0 =0?)
   
  background(back);
  restart();
}

void restart() {
  x = int(random(100,700));
  y = int(random(100,400));
  vx=2;
  vy=2;
}

void draw() {
 
 
  read=arduino.analogRead(sensor);
  read2=arduino.analogRead(sensor2);

  background(back);
  
  int value = int(map(read, 0, 1023, 0, height-padheight));
  int value2 = int(map(read2, 0, 1023, 0, height-padheight));

  rect(0, value, padwidth, padheight);
  rect(1024-padwidth, value2, padwidth, padheight);
  ellipse(x, y, bx, by);
  text(str(p0score), 10, 10);
  text(str(p1score), 1010, 10);

  x += vx;
  y += vy;
  
  if (x > (width-padwidth)) {
   if (value2-y > padheight) {
     p0score++;
     restart();
   }
   vx = -vx;
  }
  else if (x < padwidth) {
   if (value-y > padheight) {
     p1score++;
     restart();
   }
   vx = -vx;
  }

  if (y > height) vy = - vy;
  else if (y < 0) vy = -vy;

}

