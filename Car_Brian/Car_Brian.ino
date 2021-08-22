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

#define ir_receiver_1_pin 3
#define ir_receiver_2_pin 4

//Object Declarations
IRrecv IrReceiver1;
IRrecv IrReceiver2;

L298NX2 motors(left_motor_en_pin, left_motor_in1_pin, left_motor_in2_pin, right_motor_en_pin, right_motor_in1_pin, right_motor_in2_pin);

Servo myservo;

//DRIVE MODE
//Change to ir for ir or auto for autonomous
String driveMode = "bt";

void setup()
{
    // Set motor speeds
    motors.setSpeedA(150); // Left Motor
    motors.setSpeedB(130); // Right Motor

    // Initiate pin of IrReceiver and IrReceiver2 objects
    /* IrReceiver.setReceivePin(ir_receiver_pin); */
    /* IrReceiver.enableIRIn(); */
    IrReceiver1.begin(ir_receiver_1_pin);
    IrReceiver2.begin(ir_receiver_2_pin);

    // Declare pin of myservo object
    /* myservo.attach(servo_pin); */

    // Start serial communication
    Serial.begin(9600);
}

// IR Specific Variables
long time_since_last_signal = 0; // Tracks the time between *received* signals
unsigned long last_millis = 0;
int continued_signal_wait_time = 150; // Number of milliseconds to wait for a repeated signal (ideally would be controller emitting delay)

// BT Specific Variables
String bt_input = "";

void loop()
{
    switch (driveMode)
    {
    case "ir":
        IRMode();
        break;

    case "bt":
        BTMode();
        break;

    case "auto":
        AutoMode();
        break;
    }
}

void resetMotors()
{
    motors.reset();
    bt_input = "";
}

//Help function that runs whenever an IR
//Signal is recieved
void handleIRCode(IRrecv &IR_rec)
{
    // Reset timer
    time_since_last_signal = 0;

    // Print out protocol number
    Serial.print("Protocol: ");
    Serial.println(IR_rec.decodedIRData.protocol);

    // Print out data in hexadecimal
    Serial.print("0x");
    Serial.println(IR_rec.decodedIRData.address, HEX);

    // Handle Different Direction Signals
    switch (IR_rec.decodedIRData.address)
    {
    case 0x1111:
        Serial.println("-> Up Signal Received");
        motors.forward();
        break;
    case 0x2222:
        Serial.println("-> Right Signal Received");
        motors.forwardA();
        motors.backwardB();
        break;
    case 0x3333:
        Serial.println("-> Down Signal Received");
        motors.backward();
        break;
    case 0x4444:
        Serial.println("-> Left Signal Received");
        motors.backwardA();
        motors.forwardB();
        break;
    }

    // Serial monitor data separator
    Serial.println()
}

/*** Infrared Signal Handling ***/
void IRMode()
{
    // If data is available on first receiver
    if (IrReceiver1.decode())
    {
        if (IrReceiver.decodedIRData.protocol != 0)
            handleIRCode(IrReceiver1);
        // Reset and prepare to receive more data
        IrReceiver1.resume();
    }

    // If data is available on second receiver
    else if (IrReceiver2.decode())
    {
        if (IrReceiver2.decodedIRData.protocol != 0)
        {
            handleIRCode(IrReceiver2);
        }
        // Reset and prepare to receive more data
        IrReceiver2.resume();
    }
    // If {continued_signal_wait_time}ms passes without a signal
    else if ((time_since_last_signal > continued_signal_wait_time))
    {
        motors.stop();
    }

    // Update timer every ms
    if (millis() > last_millis)
    {
        time_since_last_signal += (millis() - last_millis);
        last_millis = millis();
    }
}

/*** Bluetooth Signal Handling ***/
void BTMode()
{
    // If data is available
    if (Serial.available() > 0)
    {
        bt_input = Serial.readStringUntil('\n');
        Serial.println(bt_input);
        Serial.println(bt_input.toInt());
    }

    // Handle valid inputs

    //<F> key to stop stop
    if (bt_input.endsWith("f"))
    {
        motors.stop();
    }

    //<W> key to move forwards
    else if (bt_input.endsWith("w"))
    {
        //Run for set time
        if (bt_input.toInt())
        {
            motors.forwardFor(bt_input.toInt(), resetMotors);
        }
        //Run until new command sent
        else
        {
            motors.forward();
        }
    }

    //<A> key to rotate left
    else if (bt_input.endsWith("a"))
    {
        //Run for set time
        if (bt_input.toInt())
        {
            motors.backwardForA(bt_input.toInt(), resetMotors);
            motors.forwardForB(bt_input.toInt(), resetMotors);
        }
        //Run until new command sent
        else
        {
            motors.backwardA();
            motors.forwardB();
        }
    }

    //<S> key to move back
    else if (bt_input.endsWith("s"))
    {
        //Run for set time
        if (bt_input.toInt())
        {
            motors.backwardFor(bt_input.toInt(), resetMotors);
        }
        //Run until new command sent
        else
        {
            motors.backward();
        }
    }

    //<D> key to rotate right
    else if (bt_input.endsWith("d"))
    {
        //Run for set time
        if (bt_input.toInt())
        {
            motors.forwardForA(bt_input.toInt(), resetMotors);
            motors.backwardForB(bt_input.toInt(), resetMotors);
        }

        //Run until new command sent
        else
        {
            motors.forwardA();
            motors.backwardB();
        }
    }
}

void autoMode()
{
    Serial.println("Automode");
}
