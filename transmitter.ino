/*
    Wireless Transmitter - James Boncek - circa 2013
    Map the Acceleration and Deceleration signal from the analog joystick
    and send a corresponding value to the receiver
 */

const int led = 13;
const int brakeswitch = 3;
const int selectPin = 2;
const int joystick_xPin = A0;
const int joystick_yPin = A5;
int oldX = 0;
int oldY = 0;
int oldSelect = 0;

void setup()
{
    pinMode(selectPin, INPUT);
    pinMode(brakeswitch, OUTPUT);
    digitalWrite(brakeswitch, LOW);
    digitalWrite(selectPin, HIGH);
    digitalWrite(led, HIGH);
    Serial.begin(57600);
}

void loop()
{
    int joystick_y;

    joystick_y = map(analogRead(joystick_yPin), 0, 1023, 0, 100);
    select = !digitalRead(selectPin);

    // Define center, and do nothing
    if (joystick_y >= 49 && joystick_y <= 51)
    {
        Serial.write(joystick_y);
    }

    // acceleration
    if (joystick_y > 51)
    {

        // check brake switch - stop it
        if (digitalRead(brakeswitch) == HIGH)
        {
            digitalWrite(brakeswitch, LOW);
        }

        //      Serial.println("Accelerating at ");
        Serial.write(joystick_y);
    }

    // braking
    if (joystick_y < 49)
    {

        // set/check brake switch
        if (digitalRead(brakeswitch) == LOW)
        {
            digitalWrite(brakeswitch, HIGH);
        }

        //      Serial.println("Braking at ");
        Serial.write(joystick_y);
    }

    delay(100);
} // loop
