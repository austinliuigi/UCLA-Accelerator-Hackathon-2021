#define led 6
#include <HCSR04.h>

#define left_motor_enable_pin 5
#define left_motor_input1_pin 6
#define left_motor_input2_pin 7
#define right_motor_input1_pin 8
#define right_motor_input2_pin 9
#define right_motor_enable_pin 10


int trigger = 11;
int echo = 12;

UltraSonicDistanceSensor distanceSensor(trigger, echo);

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  // Set pins
    pinMode(left_motor_enable_pin, OUTPUT);
    pinMode(right_motor_enable_pin, OUTPUT);
    pinMode(left_motor_input1_pin, OUTPUT);
    pinMode(left_motor_input2_pin, OUTPUT);
    pinMode(right_motor_input1_pin, OUTPUT);
    pinMode(right_motor_input2_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  double distance = distanceSensor.measureDistanceCm();
  Serial.print("Distance of object to Sensor is: ");
  Serial.println(distance);

 if (distance > 4.5){
  moveForwards();
 }
 else if (distance < 4.5){
  Serial.println("front wall detected ->turn right");
  turnRight();

  delay(800); // check if it turns 90 degrees
  distance = distanceSensor.measureDistanceCm();

  if (distance < 4.5) {
    Serial.println("right was detected - > turn left");
    turnLeft();

    delay(1600);
  }
 }
}

  unsigned int max_speed = 150;

void moveForwards()
{
    // Set both motors to go forwards
    digitalWrite(left_motor_input1_pin, HIGH);
    digitalWrite(left_motor_input2_pin, LOW);
    digitalWrite(right_motor_input1_pin, HIGH);
    digitalWrite(right_motor_input2_pin, LOW);

    // Enable motors at specific speed
    analogWrite(left_motor_enable_pin, max_speed);
    analogWrite(right_motor_enable_pin, max_speed);

    Serial.println("-> moveForwards Function Called");
}

void turnRight()
{
    // Set left motor to go forwards
    digitalWrite(left_motor_input1_pin, HIGH);
    digitalWrite(left_motor_input2_pin, LOW);

    // Set right motor to go backwards
    digitalWrite(right_motor_input1_pin, LOW);
    digitalWrite(right_motor_input2_pin, HIGH);

    // Enable motors at specific speed
    analogWrite(left_motor_enable_pin, max_speed);
    analogWrite(right_motor_enable_pin, max_speed);

    Serial.println("-> turnRight Function Called");
}


void turnLeft()
{
    // Set left motor to go backwards
    digitalWrite(left_motor_input1_pin, LOW);
    digitalWrite(left_motor_input2_pin, HIGH);

    // Set right motor to go forwards
    digitalWrite(right_motor_input1_pin, HIGH);
    digitalWrite(right_motor_input2_pin, LOW);

    // Enable motors at specific speed
    analogWrite(left_motor_enable_pin, max_speed);
    analogWrite(right_motor_enable_pin, max_speed);

    Serial.println("-> turnLeft Function Called");
}
