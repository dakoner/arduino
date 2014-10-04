// Use the included processing code serial library
import processing.serial.*;        


Serial port;                         // The serial port

boolean moving = false;
int movingTime = 0;
void setup() 
{

  size(180, 180);
  colorMode(RGB, 1.0);
  noSmooth();
  frameRate(100);
  println(Serial.list()); // List COM-ports

  //select second com-port from the list
  port = new Serial(this, Serial.list()[0], 9600);
  port.write("93s");
  port.write("92w");
}

void draw() 
{
  background(0.0);
  rect(20, 20, 40, 40); 

  rect(60, 20, 40, 40); 

  rect(20, 80, 40, 40); 

  rect(60, 80, 40, 40); 
  //Calculate servo postion from mouseX
  if (moving) {
    if (millis() - movingTime > 5) {
      println("Stopping");
      port.write("93s");
      port.write("92w");
      moving = false;
      movingTime = 0;
    }
    return;
  }
  //Output the servo position ( from 0 to 180)
  if (mousePressed) {
    println("Mouse pressed: ", mouseX, " ", mouseY);
    if (mouseX >= 20 && mouseX <= 60 && mouseY >= 20 && mouseY <= 60) {
      println("pressed 1");
      port.write("89s");
      moving = true;
      movingTime = millis();
    } else if (mouseX >= 60 && mouseX <= 100 && mouseY >= 20 && mouseY <= 60) {
      println("pressed 2");
      port.write("96s");
      moving = true;
      movingTime = millis();
    } else if (mouseX >= 20 && mouseX < 60 && mouseY >= 80 && mouseY <= 120) {
      println("pressed 3");
      port.write("89w");
      moving = true;
      movingTime = millis();
    } else if (mouseX >= 60 && mouseX <= 100 && mouseY >= 80 && mouseY <= 120) {
      println("pressed 4");
      port.write("96w");
      moving = true;
      movingTime = millis();
    }
  }
  if (moving) println("Moving");
  //port.write("w"+mouseY);
}

