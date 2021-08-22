// Autonomous Car + reading maze + turning
// Ultrasonic on right side
// Reflective IR on left side

#include <HCSR04.h>  //ultrasonic library
#include <L298NX2.h> //motor library
#include <Servo.h>

// Initialize ultrasonic sensor 
int triggerPin = 11;
int echoPin = 12;
double distUltra;               // value read from ultrasensor 
double UltraWallDist = 4.5;     // distance of wall to sensor

UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

//Initialize IR sensor 
#define IRsensor A0
int distIR;                     // value that the IRsensor is reading
int IRWallDist = 200;           //NEED to test with maze

//Initialize motors
#define left_motor_en_pin 5
#define left_motor_in1_pin 6
#define left_motor_in2_pin 7
#define right_motor_in1_pin 8
#define right_motor_in2_pin 9
#define right_motor_en_pin 10

L298NX2 motors(left_motor_en_pin, left_motor_in1_pin, left_motor_in2_pin, 
right_motor_en_pin, right_motor_in1_pin, right_motor_in2_pin);

//Initialize servo for unloading code
Servo myservo;

void setup() {
   Serial.begin(9600); // initialize serial connection
   pinMode(IRsensor, INPUT); 

    // Set motor speeds
    motors.setSpeedA(150);  // Left Motor
    motors.setSpeedB(130);  // Right Motor

    //Add servo unloading stuff
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
     motors.forward(); //move forward when no wall is detected
  }
  if (distIR > IRWallDist && distUltra < UltraWallDist){
      // turn left + move forward a bit
     Serial.println("Left path detected -> turning left");
     motors.backwardA();
     motors.forwardB();
       //also need to experiment this to turn 90
     delay(1000);
     distIR = analogRead(A0);
  }
  if (distIR < IRWallDist && distUltra > UltraWallDist){
      // turn right + move forward a bit
     Serial.println("Right path detected -> turning right");
     motors.forwardA();
     motors.backwardB();
      //also need to experiment this to turn 90
     delay(1000);
     distUltra = distanceSensor.measureDistanceCm(); 
  }
  if(distIR > IRWallDist && distUltra > UltraWallDist){
    motors.stop(); //stop
    //unload
   delay(5000); 
  }
  
}
