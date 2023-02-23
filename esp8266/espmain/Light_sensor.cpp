#include "Light_sensor.h"
#include "Arduino.h"

Light_sensor::Light_sensor(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
  Serial.print("Light Sensor starting...");
}




int Light_sensor::getLightLevel(){
    int light = analogRead(pin);
    return light;

};
