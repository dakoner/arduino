#include <NewPing.h>

#define TRIGGER_PIN  16
#define ECHO_PIN     17
#define MAX_DISTANCE 200
#define STOP_DISTANCE   8

template <typename V, int N> class MovingAverage
{
public:
    /*
     * @brief Class constructor.
     * @param def the default value to initialize the average.
     */
    MovingAverage(V def = 0) : sum(0), p(0)
    {
        for (int i = 0; i < N; i++) {
            samples[i] = def;
            sum += samples[i];
        }
    }

    /*
     * @brief Add a new sample.
     * @param new_sample the new sample to add to the moving average.
     * @return the updated average.
     */
    V add(V new_sample)
    {
        sum = sum - samples[p] + new_sample;
        samples[p++] = new_sample;
        if (p >= N)
            p = 0;
        return sum / N;
    }

private:
    V samples[N];
    V sum;
    V p;
};

NewPing DistanceSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
MovingAverage<unsigned int, 3> average;
enum state_t { FORWARD, TURNING, REVERSE };
state_t state;
unsigned long startTime = millis();


void setup()
{
  Serial.begin(57600);
    
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel B pin
  
   state = FORWARD;
   
   digitalWrite(12, LOW); //Establishes backward direction of Channel A
   digitalWrite(9, LOW);   //Disengage the Brake for Channel A
   analogWrite(3, 255);   //Spins the motor on Channel A at full speed

   digitalWrite(13, LOW);  //Establishes backward direction of Channel B
   digitalWrite(8, LOW);   //Disengage the Brake for Channel B
   analogWrite(11, 255);    //Spins the motor on Channel B at half speed
}

void loop()
{
   unsigned long currentTime = millis();
   unsigned long delta = currentTime-startTime;
   unsigned int cm = DistanceSensor.ping_cm();
   int distance = average.add(cm);
   int current0 = analogRead(A0);
    int current1 = analogRead(A1);
  
    Serial.print("Distance: ");
    Serial.println(cm);
    Serial.print("cm, avg: ");
    Serial.print(distance);
    Serial.print("cm elapsed:");
    Serial.print(currentTime-startTime);
    Serial.print(" motor A current: ");
    
    Serial.print(         current0);
    Serial.print(" motor B current: ");
    Serial.print(         current1);
    Serial.println();


    // If we're turning, and there's nothing in front of us, go.
    state_t newstate = state;
/*    
    if ((state == FORWARD || state == REVERSE) && (current0 >= 90 || current1 >= 90)) {
       Serial.println("was going forwrad or reverse, got stuck, switching");
       if (state == FORWARD) {
         digitalWrite(12, HIGH); //Establishes backward direction of Channel A
         digitalWrite(9, LOW);   //Disengage the Brake for Channel A
         analogWrite(3, 255);   //Spins the motor on Channel A at full speed
         digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
         digitalWrite(8, LOW);   //Disengage the Brake for Channel B
         analogWrite(11, 255);    //Spins the motor on Channel B at half speed
         newstate=REVERSE;
       }
       if (state == REVERSE) {
         digitalWrite(12, LOW); //Establishes backward direction of Channel A
         digitalWrite(9, LOW);   //Disengage the Brake for Channel A
         analogWrite(3, 255);   //Spins the motor on Channel A at full speed
         digitalWrite(13, LOW);  //Establishes backward direction of Channel B
         digitalWrite(8, LOW);   //Disengage the Brake for Channel B
         analogWrite(11, 255);    //Spins the motor on Channel B at half speed
         newstate=FORWARD;
       }
    }    
    else */
    if (state == TURNING && distance > STOP_DISTANCE && delta > 250) {
        Serial.println("was turning , now no barrier, starting forward");
 
        digitalWrite(12, LOW); //Establishes backward direction of Channel A
        digitalWrite(9, LOW);   //Disengage the Brake for Channel A
        analogWrite(3, 255);   //Spins the motor on Channel A at full speed

        digitalWrite(13, LOW);  //Establishes backward direction of Channel B
        digitalWrite(8, LOW);   //Disengage the Brake for Channel B
        analogWrite(11, 255);    //Spins the motor on Channel B at half speed
        
        newstate=FORWARD;
     }
     else if (state == FORWARD && distance <= STOP_DISTANCE && delta > 250) {
       Serial.println("was going forwrad, hit barrier, turning");

       if (random(2) == 0) {
         digitalWrite(12, LOW); //Establishes backward direction of Channel A
         digitalWrite(9, LOW);   //Disengage the Brake for Channel A
         analogWrite(3, 255);   //Spins the motor on Channel A at full speed

         digitalWrite(13, HIGH);  //Establishes backward direction of Channel  B
         digitalWrite(8, LOW);   //Disengage the Brake for Channel B
         analogWrite(11, 255);    //Spins the motor on Channel B at half speed
       } else {
         digitalWrite(12, HIGH); //Establishes backward direction of Channel A
         digitalWrite(9, LOW);   //Disengage the Brake for Channel A
         analogWrite(3, 255);   //Spins the motor on Channel A at full speed

         digitalWrite(13, LOW);  //Establishes backward direction of Channel B
         digitalWrite(8, LOW);   //Disengage the Brake for Channel B
         analogWrite(11, 255);    //Spins the motor on Channel B at half speed
       }
       newstate=TURNING;
     }
     
     if (newstate != state) {
       Serial.print("new state: ");
       Serial.println(newstate);
       state = newstate;
       startTime=currentTime;
     }


  // Delay so we don't swamp the serial port
  delay(1);
}

