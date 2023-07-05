#include "Light_sensor.h"
#include "Arduino.h"

Light_sensor::Light_sensor(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
  Serial.print("Light Sensor starting...");
}




double Light_sensor::getLightLevel(){
    int light = analogRead(pin);
    double value = ((double) light) * 100/1023;
    return value;

};
