//ultrasonic autonomous car

#include <HCSR04.h>

// Initialize sensor that uses digital pins 13 and 12.
int triggerPin = 11;
int echoPin = 12;
const int led = 7;

UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
    pinMode(led, OUTPUT);
    
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    double distance = distanceSensor.measureDistanceCm();
    Serial.println(distance);
    delay(500);

    
 digitalWrite(led, HIGH);
  delay(100);
    digitalWrite(led, LOW);// reading distance when led is dim
  delay(100);
}




/*
const int led = 12;
const int Trig = 6;
const int Echo = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("hello world");
  digitalWrite(led, LOW);// reading distance when led is dim
  delay(100);
  
  digitalWrite(Trig, HIGH); //sensing distance
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  int reading = pulseIn(Echo, HIGH); //put distance in variable 
  Serial.println(reading);                    // to print
  
  digitalWrite(led, HIGH);
  delay(100);
  
}
*/
