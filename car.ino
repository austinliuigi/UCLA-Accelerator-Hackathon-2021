#include <IRremote.h>
#include <Servo.h>

#define left_motor_enable_pin 5
#define left_motor_input1_pin 6
#define left_motor_input2_pin 7
#define right_motor_input1_pin 8
#define right_motor_input2_pin 9
#define right_motor_enable_pin 10
#define servo_pin 3
#define ir_receiver_pin 4

Servo myservo;

void setup() {
    // Declare pin of IrReceiver object
    /* IrReceiver.setReceivePin(ir_receiver_pin); */
    /* IrReceiver.enableIRIn(); */
    IrReceiver.begin(ir_receiver_pin);

    // Declare pin of myservo object
    /* myservo.attach(servo_pin); */

    // Set pins
    pinMode(left_motor_enable_pin, OUTPUT);
    pinMode(right_motor_enable_pin, OUTPUT);
    pinMode(left_motor_input1_pin, OUTPUT);
    pinMode(left_motor_input2_pin, OUTPUT);
    pinMode(right_motor_input1_pin, OUTPUT);
    pinMode(right_motor_input2_pin, OUTPUT);

    // Start serial communication
    Serial.begin(9600);
}

long time_since_last_signal = 0;        // Tracks the time between *received* signals
unsigned long last_millis = 0;
int continued_signal_wait_time = 150;    // Number of milliseconds to wait for a repeated signal (ideally would be controller emitting delay)
unsigned int max_speed = 150;           // Value from 0 to 255

void loop() {
    // If data is available
    if (IrReceiver.decode())
    {
        if (IrReceiver.decodedIRData.protocol != 0)
        {
            // Reset timer
            time_since_last_signal = 0;
            
            // Print out protocol number
            Serial.print("Protocol: ");
            Serial.println(IrReceiver.decodedIRData.protocol);
          
            // Print out data in hexadecimal
            Serial.print("0x");
            Serial.println(IrReceiver.decodedIRData.address, HEX);
            
            // Handle up signal
            if (IrReceiver.decodedIRData.address == 0x1111)
            {
                Serial.println("-> Up Signal Received");
                moveForwards();
            }
            // Handle right signal
            else if (IrReceiver.decodedIRData.address == 0x2222)
            {
                Serial.println("-> Right Signal Received");
                turnRight();
            }
            // Handle down signal
            else if (IrReceiver.decodedIRData.address == 0x3333)
            {
                Serial.println("-> Down Signal Received");
                moveBackwards();
            }
            // Handle left signal
            else if (IrReceiver.decodedIRData.address == 0x4444)
            {
                Serial.println("-> Left Signal Received");
                turnLeft();
            }

            // Serial monitor data separator
            Serial.println();
        }
        // Reset and prepare to receive more data
        IrReceiver.resume();
    }
    // If {continued_signal_wait_time}ms passes without a signal
    else if (time_since_last_signal > continued_signal_wait_time)
    {
        // Stop motors
        analogWrite(left_motor_enable_pin, 0);
        analogWrite(right_motor_enable_pin, 0);
    }

    // Update timer every ms
    if (millis() > last_millis)
    {
        time_since_last_signal += (millis() - last_millis);
        last_millis = millis();
    }

    //Serial.println(time_since_last_signal);
    //delay(50);
}

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

void moveBackwards()
{
    // Set both motors to go backwards
    digitalWrite(left_motor_input1_pin, LOW);
    digitalWrite(left_motor_input2_pin, HIGH);
    digitalWrite(right_motor_input1_pin, LOW);
    digitalWrite(right_motor_input2_pin, HIGH);

    // Enable motors at specific speed
    analogWrite(left_motor_enable_pin, max_speed);
    analogWrite(right_motor_enable_pin, max_speed);

    Serial.println("-> moveBackwards Function Called");
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
