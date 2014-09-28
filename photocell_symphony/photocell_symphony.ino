void setup() {
  // initialize serial communications (for debugging only):
  //Serial.begin(9600);
}

void loop() {
  // read the sensor:
  int sensorReading = analogRead(1);
 // int sensorReading2 = analogRead(A1);

  // print the sensor reading so you know its range
  //Serial.print(sensorReading);
  //Serial.print(" ");
  //Serial.println(sensorReading2);

  // map the analog input range (in this case, 400 - 1000 from the photoresistor)
  // to the output pitch range (120 - 1500Hz)
  // change the minimum and maximum input numbers below
  // depending on the range your sensor's giving:
  int thisPitch = map(sensorReading, 150, 900, 50, 1500);
  //int thisPitch2 = map(sensorReading2, 150, 900, 50, 1500);

  // play the pitch:
  tone(9, thisPitch, 10);
  delay(10);
  //noTone(9); 
  //tone(8, thisPitch2, 10);
  //delay(10);        // delay in between reads for stability
  //noTone(8);
}
