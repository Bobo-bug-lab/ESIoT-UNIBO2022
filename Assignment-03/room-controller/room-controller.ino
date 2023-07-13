#include <Servo.h>
#include <SoftwareSerial.h>

const byte PIN_SERVO = 11;
const byte PIN_LED = 13;
const byte PIN_BT_RX = 8;
const byte PIN_BT_TX = 7;

Servo roller;
SoftwareSerial bt_serial(PIN_BT_RX, PIN_BT_TX);

void setup()
{
    roller.attach(PIN_SERVO);
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BT_RX, INPUT);
    pinMode(PIN_BT_TX, OUTPUT);
    Serial.begin(9600);
    bt_serial.begin(9600);
}

void loop()
{
    String recv_buf = "";
    recv_buf = Serial.readStringUntil('\n');
    if (recv_buf.length() == 0)
    {
        recv_buf = bt_serial.readStringUntil('\n');
    }
    if (recv_buf.length() > 0)
    {
        // Serial.println("received:" + recv_buf);
        if (recv_buf.charAt(1) == 'L')
        {
            if (recv_buf.charAt(2) == '1') // turn on led
            {
                digitalWrite(PIN_LED, 1);
            }
            else if (recv_buf.charAt(2) == '0') // turn off led
            {
                digitalWrite(PIN_LED, 0);
            }
            recv_buf.toUpperCase();
            Serial.println(recv_buf);
        }

        else if (recv_buf.charAt(1) == 'R')
        {
            int percentage = recv_buf.substring(2).toInt();
            roller.writeMicroseconds(1000 + percentage * 10);
            recv_buf.toUpperCase();
            Serial.println(recv_buf);
        }
    }
}
