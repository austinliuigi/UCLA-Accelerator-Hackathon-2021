#include <IRremote.h>

#define left_joystick_x_pin A0
#define left_joystick_y_pin A1
#define left_joystick_sw__pin 7
#define right_joystick_x_pin A2
#define right_joystick_y_pin A3
#define right_joystick_sw__pin 8
#define ir_emitter_pin 3

void setup() {
    // Set pins
    pinMode(left_joystick_x_pin    , INPUT);
    pinMode(left_joystick_y_pin    , INPUT);
    pinMode(left_joystick_sw__pin  , INPUT);
    pinMode(right_joystick_x_pin   , INPUT);
    pinMode(right_joystick_y_pin   , INPUT);
    pinMode(right_joystick_sw__pin , INPUT);
    pinMode(ir_emitter_pin         , OUTPUT);

    // Declare pin of IrSender object
    IrSender.setSendPin(ir_emitter_pin);

    // Start serial communication
    Serial.begin(9600);
}

int left_joystick_x_pos = 0;
int left_joystick_y_pos = 0;
int right_joystick_x_pos = 0;
int right_joystick_y_pos = 0;
const uint16_t up_address = 0x1111;
const uint16_t right_address = 0x2222;
const uint16_t down_address = 0x3333;
const uint16_t left_address = 0x4444;
const uint8_t command = 0x87;
const int num_of_repeats = 0;

void loop() {
    // Calculate joystick positions
    left_joystick_x_pos = (analogRead(left_joystick_x_pin) - 512);
    left_joystick_y_pos = ((1023 - analogRead(left_joystick_y_pin)) - 512);
    right_joystick_x_pos = (analogRead(right_joystick_x_pin) - 512);
    right_joystick_y_pos = ((1023 - analogRead(right_joystick_y_pin)) - 512);

    /* Serial.print("("); */
    /* Serial.print(left_joystick_x_pos); */
    /* Serial.print(", "); */
    /* Serial.print(left_joystick_y_pos); */
    /* Serial.println(")"); */
    /* Serial.println(); */

    // Don't allow diagonal positions
    if (!(left_joystick_x_pos == left_joystick_y_pos))
    {
        if ((left_joystick_x_pos < left_joystick_y_pos) && (left_joystick_y_pos > 50))
        {
            IrSender.sendNEC(up_address, command, num_of_repeats);
        }
        if ((left_joystick_x_pos > left_joystick_y_pos) && (left_joystick_x_pos > 50))
        {
            IrSender.sendNEC(right_address, command, num_of_repeats);
        }
        if ((left_joystick_x_pos > left_joystick_y_pos) && (left_joystick_y_pos < -50))
        {
            IrSender.sendNEC(down_address, command, num_of_repeats);
        }
        if ((left_joystick_x_pos < left_joystick_y_pos) && (left_joystick_x_pos < -50))
        {
            IrSender.sendNEC(left_address, command, num_of_repeats);
        }
    }
    delay(50);
}
