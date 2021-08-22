// Autonomous Car + reading maze + turning
// Ultrasonic on right side
// Reflective IR on left side
#include <HCSR04.h>

// Initialize ultrasonic sensor 
int triggerPin = 11;
int echoPin = 12;
double distUltra;
double UltraWallDist = 4.5;
const int led = 7; // for troubleshooting
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

//Initialize IR sensor 
#define IRsensor A0
int distIR;
int IRWallDist = 200;  //NEED to test with maze

void setup() {
   Serial.begin(9600); // initialize serial connection for printing values from sensor.
    pinMode(led, OUTPUT); // for troubleshooting
    pinMode(IRsensor, INPUT); 

}

void loop() {
   // Every 500 miliseconds, do a measurement using the ultrasonic sensor 
    //and print the distance in centimeters.
    distUltra = distanceSensor.measureDistanceCm();
    //Measure Reflective IR values 0-1024
    distIR = analogRead(A0);
    
    Serial.print("Ultrasonic distance(cm): ");
    Serial.println(distUltra);
     Serial.print("IR distance(0-1024): ");
    Serial.println(distIR);
    //delay (500);

   
  if(distIR < IRWallDist && distUltra < UltraWallDist){
    //move forward 
  }
  if (distIR > IRWallDist && distUltra < UltraWallDist){
    // turn left + move forward a bit
  }
  if (distIR < IRWallDist && distUltra > UltraWallDist){
    // turn right + move forward a bit
  }
  if(distIR > IRWallDist && distUltra > UltraWallDist){
    //stop
    //unload
  }

}
