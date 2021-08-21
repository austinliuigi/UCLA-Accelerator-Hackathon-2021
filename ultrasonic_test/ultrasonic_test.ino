//ultrasonic autonomous car

#include <HCSR04.h>

#define left_motor_enable_pin 5
#define left_motor_input1_pin 6
#define left_motor_input2_pin 7
#define right_motor_input1_pin 8
#define right_motor_input2_pin 9
#define right_motor_enable_pin 10


// Initialize sensor 
int triggerPin = 11;
int echoPin = 12;
const int led = 7; // for troubleshooting

UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup () {
    Serial.begin(9600);  
    // initialize serial connection for printing values from sensor.
    pinMode(led, OUTPUT);

    // Set pins
    pinMode(left_motor_enable_pin, OUTPUT);
    pinMode(right_motor_enable_pin, OUTPUT);
    pinMode(left_motor_input1_pin, OUTPUT);
    pinMode(left_motor_input2_pin, OUTPUT);
    pinMode(right_motor_input1_pin, OUTPUT);
    pinMode(right_motor_input2_pin, OUTPUT);
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor 
    //and print the distance in centimeters.
    double distance = distanceSensor.measureDistanceCm();
    Serial.println(distance);
    //delay (500);
    
    if (distance > 4.5){
       moveForwards();   //move forward when no wall is detected
       
    } 
    else if (distance < 4.5){  //turn right 90 degrees
       Serial.println("Front wall detected -> turning right");
       turnRight();
       
       //We need to experiment with this, so it can actually turn 90
       delay(1000);     
       //Measure dist again for the right wall
       distance = distanceSensor.measureDistanceCm(); 
       
        if (distance < 4.5){ //turn left 180 degrees
          Serial.println("Right wall detected -> turning left");
          turnLeft();
          
          //also need to experiment this to turn 180
          delay(1600);  
        }
    }
  //  troubleshoot();
}

void troubleshoot()
{
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);
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
