#include <L298NX2.h>
#include <IRremote.h>
#include <Servo.h>

#define left_motor_en_pin 5
#define left_motor_in1_pin 6
#define left_motor_in2_pin 7
#define right_motor_in1_pin 8
#define right_motor_in2_pin 9
#define right_motor_en_pin 10
#define servo_pin 3
#define ir_receiver_pin 4

L298NX2 motors(left_motor_en_pin, left_motor_in1_pin, left_motor_in2_pin, right_motor_en_pin, right_motor_in1_pin, right_motor_in2_pin);

Servo myservo;

void setup() {
    // Initiate pin of IrReceiver object
    /* IrReceiver.setReceivePin(ir_receiver_pin); */
    /* IrReceiver.enableIRIn(); */
    IrReceiver.begin(ir_receiver_pin);

    // Declare pin of myservo object
    /* myservo.attach(servo_pin); */

    // Set motor values
    motors.setSpeedA(150);  // Left Motor
    motors.setSpeedB(130);  // Right Motor

    // Start serial communication
    Serial.begin(9600);
}

// IR Specific Variables
long time_since_last_signal = 0;        // Tracks the time between *received* signals
unsigned long last_millis = 0;
int continued_signal_wait_time = 150;    // Number of milliseconds to wait for a repeated signal (ideally would be controller emitting delay)

// BT Specific Variables
String bt_input;

// Other Variables
String mode;

void loop() {
    /*** Infrared Signal Handling ***/
    // If data is available
    if (IrReceiver.decode())
    {
        if (IrReceiver.decodedIRData.protocol != 0)
        {
            // Set mode
            mode = "ir";

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
                motors.forward();
            }
            // Handle right signal
            else if (IrReceiver.decodedIRData.address == 0x2222)
            {
                Serial.println("-> Right Signal Received");
                motors.forwardA();
                motors.backwardB();
            }
            // Handle down signal
            else if (IrReceiver.decodedIRData.address == 0x3333)
            {
                Serial.println("-> Down Signal Received");
                motors.backward();
            }
            // Handle left signal
            else if (IrReceiver.decodedIRData.address == 0x4444)
            {
                Serial.println("-> Left Signal Received");
                motors.backwardA();
                motors.forwardB();
            }

            // Serial monitor data separator
            Serial.println();
        }
        // Reset and prepare to receive more data
        IrReceiver.resume();
    }
    // If {continued_signal_wait_time}ms passes without a signal
    else if ((time_since_last_signal > continued_signal_wait_time) && (mode == "ir"))
    {
        motors.stop();
    }

    // Update timer every ms
    if (millis() > last_millis)
    {
        time_since_last_signal += (millis() - last_millis);
        last_millis = millis();
    }

    /*** Bluetooth Signal Handling ***/
    // If data is available
    if (Serial.available() > 0)
    {
        // Set mode
        mode = "bt";

        bt_input = Serial.readStringUntil('\n');
        Serial.println(bt_input);

        switch (bt_input[0])
        {
            // Freeze(Stop)
            case 'f':
                motors.stop();
                break;
            // Forward
            case 'w':
                motors.forward();
                break;
            // Left
            case 'a':
                motors.backwardA();
                motors.forwardB();
                break;
            // Backward
            case 's':
                motors.backward();
                break;
            // Right
            case 'd':
                motors.forwardA();
                motors.backwardB();
                break;
        }

        /* if (bt_input == "f") */
        /* { */
        /*     motors.stop(); */
        /* } */
        /* else if (bt_input == "w") */
        /* { */
        /*     motors.forward(); */
        /* } */
        /* else if (bt_input == "a") */
        /* { */
        /*     motors.backwardA(); */
        /*     motors.forwardB(); */
        /* } */
        /* else if (bt_input == "s") */
        /* { */
        /*     motors.backward(); */
        /* } */
        /* else if (bt_input == "d") */
        /* { */
        /*     motors.forwardA(); */
        /*     motors.backwardB(); */
        /* } */

    }
}
