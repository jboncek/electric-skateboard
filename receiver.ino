/*
    Wireless Receiver - James Boncek - circa 2013
    Capture Acceleration and Deceleration signal from the paired transmitter
    and send a corresponding voltage to the motor controller
*/

const int led = 13;
const int accel = 3;
const int decel = 5;
const int brakeswitch = 7;
const int precharge = 8;
const int onswitch = 12;
int accel_rate = 0;
int decel_rate = 0;
int incomingByte = 0;
int oldX = 0;
int oldY = 0;
int x = 1;

void setup()
{
    // pin setup
    pinMode(accel, OUTPUT);
    pinMode(decel, OUTPUT);
    pinMode(brakeswitch, OUTPUT);
    pinMode(precharge, OUTPUT);
    pinMode(onswitch, OUTPUT);
    digitalWrite(brakeswitch, LOW);
    digitalWrite(precharge, LOW);
    digitalWrite(onswitch, LOW);

    // precharge the controller
    if (digitalRead(precharge) == LOW)
    {
        digitalWrite(precharge, HIGH);
        delay(5000);
        digitalWrite(precharge, LOW);
    }

    // turn on high current
    digitalWrite(onswitch, HIGH);

    // begin receiving commands
    Serial.begin(57600);
}

void loop()
{

    // read data only when it is available:
    if (Serial.available() > 0)
    {

        int joystick_y = Serial.read();

        // TODO - add constraint
        accel_rate = map(joystick_y, 53, 100, 0, 255);
        decel_rate = map(joystick_y, 47, 0, 0, 255);

        // Define center, and do nothing
        if (joystick_y >= 48 && joystick_y <= 52)
        {
            analogWrite(accel, 0);
            analogWrite(decel, 0);
            // check brake switch - stop it
            if (digitalRead(brakeswitch) == HIGH)
            {
                digitalWrite(brakeswitch, LOW);
                digitalWrite(led, LOW);
            }
        }

        // acceleration
        if (joystick_y > 52)
        {
            // check brake switch - stop it
            if (digitalRead(brakeswitch) == HIGH)
            {
                digitalWrite(brakeswitch, LOW);
                digitalWrite(led, LOW);
            }
            // send rate to accel pin
            analogWrite(decel, 0);
            analogWrite(accel, accel_rate);
        }

        // braking
        if (joystick_y < 48)
        {
            // set/check brake switch
            if (digitalRead(brakeswitch) == LOW)
            {
                digitalWrite(brakeswitch, HIGH);
                digitalWrite(led, HIGH);
            }
            analogWrite(accel, 0);
            analogWrite(decel, decel_rate);
        }
        // else old Y = currentY while serial is available
        // joystick hasn't moved or new command hasn't been received
        // possibly has lost connection...But serial is available...so it likely hasn't moved
        delay(100);
    }
    else
    { // serial is not available

        analogWrite(accel, 0);
        analogWrite(decel, 0);
        delay(100);
    }
}
