// Autonomous Car + reading maze + turning
// Ultrasonic on right side
// Reflective IR on left side
#include <HCSR04.h> //ultrasonic library

// Initialize ultrasonic sensor 
int triggerPin = 11;
int echoPin = 12;
double distUltra;               // value that the ultrasensor is reading
double UltraWallDist = 4.5;     // distance of wall to sensor
const int led = 7;              // for troubleshooting
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

//Initialize IR sensor 
#define IRsensor A0
int distIR;                     // value that the IRsensor is reading
int IRWallDist = 200;           //NEED to test with maze

//Initialize motors
#define left_motor_enable_pin 5
#define left_motor_input1_pin 6
#define left_motor_input2_pin 7
#define right_motor_input1_pin 8
#define right_motor_input2_pin 9
#define right_motor_enable_pin 10

void setup() {
   Serial.begin(9600); // initialize serial connection for printing values from sensor.
   pinMode(led, OUTPUT); // for troubleshooting
   pinMode(IRsensor, INPUT); 

    // Set motor pins
    pinMode(left_motor_enable_pin, OUTPUT);
    pinMode(right_motor_enable_pin, OUTPUT);
    pinMode(left_motor_input1_pin, OUTPUT);
    pinMode(left_motor_input2_pin, OUTPUT);
    pinMode(right_motor_input1_pin, OUTPUT);
    pinMode(right_motor_input2_pin, OUTPUT);
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
     moveForwards(); //move forward when no wall is detected
  }
  if (distIR > IRWallDist && distUltra < UltraWallDist){
          // turn left + move forward a bit
     Serial.println("Left path detected -> turning left");
     turnLeft();
          //also need to experiment this to turn 90
     delay(1000);
     distIR = analogRead(A0);
  }
  if (distIR < IRWallDist && distUltra > UltraWallDist){
             // turn right + move forward a bit
     Serial.println("Right path detected -> turning right");
     turnRight();
             //We need to experiment with this, so it can actually turn 90
     delay(1000);     
             //Measure dist again for the right wall
     distUltra = distanceSensor.measureDistanceCm(); 
  }
  if(distIR > IRWallDist && distUltra > UltraWallDist){
    //stop
    //unload
  }
  
}



//lights an led to troubleshoot
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
